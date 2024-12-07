#include "MY_MPU.h"
#include "mpu_i2c.h"
#include <util/delay.h>

#define MPU_ADDRESS 0xD0
#define MPU_ADDRESS_READ 0xD1

// Generic function to write to MPU6050 registers
static void MPU6050_writeRegister(uint8_t reg, uint8_t value) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(reg);
    I2C_Write(value);
    I2C_Stop();
}

/**
 * Sets the sample rate divider for the MPU6050
 * Final Sample Rate = (Gyroscope Output Rate)/(1 + SMPLRT_DIV)
 * @param rate: Sample rate divider value
 */
void MPU6050_setSampleRate(uint8_t rate) {
    MPU6050_writeRegister(SMPLRT_DIV, rate);
}

/**
 * Configures the clock source for the MPU6050
 * @param source: Clock source selection
 *        0x00: Internal 8MHz oscillator
 *        0x01-0x06: Various PLL settings
 *        0x07: Stops the clock
 */
void MPU6050_setClockSource(uint8_t source) {
    MPU6050_writeRegister(PWR_MGMT_1, source);
}

/**
 * Sets the full-scale range for the gyroscope
 * @param range: Gyro range setting
 *        0x00: ± 250 °/s
 *        0x08: ± 500 °/s
 *        0x10: ± 1000 °/s
 *        0x18: ± 2000 °/s
 */
void MPU6050_setGyroConfig(uint8_t range) {
    MPU6050_writeRegister(GYRO_CONFIG, range);
}

/**
 * Sets the full-scale range for the accelerometer
 * @param range: Accelerometer range setting
 *        0x00: ± 2g
 *        0x08: ± 4g
 *        0x10: ± 8g
 *        0x18: ± 16g
 */
void MPU6050_setAccelConfig(uint8_t range) {
    MPU6050_writeRegister(ACCEL_CONFIG, range);
}

/**
 * Configures the digital low-pass filter
 * @param range: DLPF configuration value
 *        Bandwidth: 260Hz, 184Hz, 94Hz, 44Hz, 21Hz, 10Hz, 5Hz
 */
void MPU6050_setLPF(uint8_t range) {
    MPU6050_writeRegister(CONFIG, range);
}

/**
 * Enables or disables interrupt generation
 * @param enable: Interrupt enable flags
 */
void MPU6050_setInterruptEnable(uint8_t enable) {
    MPU6050_writeRegister(INT_ENABLE, enable);
}

/**
 * Initializes the MPU6050 with default settings
 * - Sample rate: 1kHz
 * - Clock source: Internal 8MHz
 * - Gyro range: ±500°/s
 * - Accelerometer range: ±8g
 */
void MPU6050_init() {
    _delay_ms(150);  // Power-up time >100ms
    
    MPU6050_setSampleRate(0x07);    // 1kHz sample rate
    MPU6050_setClockSource(0x00);   // Internal 8MHz oscillator
    MPU6050_setGyroConfig(0x08);    // ±500°/s full scale
    MPU6050_setAccelConfig(0x10);   // ±8g full scale
}

/**
 * Positions the I2C read pointer at the start of sensor data registers
 */
void MPU_Start_Loc() {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(ACCEL_XOUT_H);
    I2C_Repeated_Start(MPU_ADDRESS_READ);
}

/**
 * Reads raw sensor values from MPU6050
 * @param acc: Array to store accelerometer readings (X,Y,Z)
 * @param gyro: Array to store gyroscope readings (X,Y,Z)
 */
void Read_RawValue(float acc[3], float gyro[3]) {
    MPU_Start_Loc();
    
    // Read accelerometer data (X,Y,Z)
    for(int i = 0; i < 3; i++) {
        acc[i] = ((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Ack();
    }
    
    // Skip temperature readings
    I2C_Read_Ack();
    I2C_Read_Ack();
    
    // Read gyroscope data (X,Y,Z)
    for(int i = 0; i < 2; i++) {
        gyro[i] = ((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Ack();
    }
    // Last read uses NACK
    gyro[2] = ((int)I2C_Read_Ack() << 8) | (int)I2C_Read_Nack();
    
    I2C_Stop();
}

/**
 * Calibrates the gyroscope by calculating offset values
 * @param gyro_offset: Array to store calculated offsets (X,Y,Z)
 */
void MPU6050_calibrate(float gyro_offset[3]) {
    const int num_samples = 2000;
    long gyro_total[3] = {0, 0, 0};
    
    // Collect multiple samples
    for(int i = 0; i < num_samples; i++) {
        float acc[3], gyro[3];
        Read_RawValue(acc, gyro);
        
        for(int axis = 0; axis < 3; axis++) {
            gyro_total[axis] += gyro[axis];
        }
        _delay_ms(3);
    }
    
    // Calculate average offsets
    for(int axis = 0; axis < 3; axis++) {
        gyro_offset[axis] = gyro_total[axis] / num_samples;
    }
}

/**
 * Initializes the angle state structure with zero values
 * @param state: Pointer to AngleState structure
 */
void initAngleState(AngleState* state) {
    for(int i = 0; i < 3; i++) {
        state->angles[i] = 0;
        state->gyro_angles[i] = 0;
        state->acc_angles[i] = 0;
    }
}

/**
 * Updates angle calculations using sensor fusion
 * Combines accelerometer and gyroscope data using complementary filter
 * @param state: Pointer to AngleState structure
 * @param acc: Current accelerometer readings
 * @param gyro: Current gyroscope readings
 * @param gyro_offset: Calibrated gyroscope offsets
 */
void updateAngles(AngleState* state, const float acc[3], const float gyro[3], const float gyro_offset[3]) {
    // Adjust gyroscope readings by offset
    float adjusted_gyro[3];
    for(int i = 0; i < 3; i++) {
        adjusted_gyro[i] = gyro[i] - gyro_offset[i];
    }
    
    // SSF_GYRO: Sensitivity Scale Factor of the gyro from DataSheet
    // FREQ: Sampling frequency 1000HZ
    
    // Integrate gyroscope rates to estimate angular changes (in degrees)
    // for roll (X) and pitch (Y).
    // This converts angular velocity to angle using the formula:
    // angle += rate / (frequency * sensitivity) [Definition]
    
    state->gyro_angles[X] += (adjusted_gyro[X] / (FREQ * SSF_GYRO));
    state->gyro_angles[Y] += (adjusted_gyro[Y] / (FREQ * SSF_GYRO));
    
    // Compensate for roll-pitch coupling caused by yaw motion.
    // The compensation uses a small-angle approximation based on the yaw rate.
    
    float yaw_factor = sin(adjusted_gyro[Z] * (PI / (FREQ * SSF_GYRO * 180)));
    state->gyro_angles[Y] += state->gyro_angles[X] * yaw_factor;// Add cross-coupled effect to pitch
    state->gyro_angles[X] -= state->gyro_angles[Y] * yaw_factor;// Subtract cross-coupled effect from roll
    
    // Calculate the total acceleration vector magnitude.
    // Used for deriving angles based on accelerometer readings.
    float acc_total_vector = sqrt((acc[X] * acc[X]) + 
                                (acc[Y] * acc[Y]) + 
                                (acc[Z] * acc[Z]));
    
    // Calculate accelerometer-derived angles for roll and pitch.
    // Only valid when the acceleration component along one axis is less than the total vector magnitude.
    if(fabs(acc[X]) < acc_total_vector) {
        state->acc_angles[X] = asin((float)acc[Y] / acc_total_vector) * (180 / PI);// Roll angle
    }
    if(fabs(acc[Y]) < acc_total_vector) {
        state->acc_angles[Y] = asin((float)acc[X] / acc_total_vector) * (180 / PI);// Pitch angle
    }
    
    // Fuse gyroscope and accelerometer data using a complementary filter.
    // The filter combines 96% of the gyro data (short-term accuracy) and 4% of the accelerometer data (long-term stability).
    for(int i = 0; i < 2; i++) {
        state->gyro_angles[i] = state->gyro_angles[i] * 0.96 + state->acc_angles[i] * 0.04;
    }
    
    // Apply a final smoothing filter to reduce noise in the calculated angles.
    // The filter weighs 70% of the previous angle estimate and 30% of the newly calculated angle.
    state->angles[X] = state->angles[X] * 0.7 + state->gyro_angles[X] * 0.3;// Smoothed roll
    state->angles[Y] = state->angles[Y] * 0.7 + state->gyro_angles[Y] * 0.3;// Smoothed pitch
    state->angles[Z] = -adjusted_gyro[Z] / SSF_GYRO;// Yaw estimation based on gyroscope
}