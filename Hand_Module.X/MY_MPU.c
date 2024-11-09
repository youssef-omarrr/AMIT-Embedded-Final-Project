#include "MY_MPU.h"
#include "mpu_i2c.h"
#include <util/delay.h>

#define MPU_ADDRESS 0xD0
#define MPU_ADDRESS_READ 0xD1

float Acc_x, Acc_y, Acc_z, Temperature, Gyro_x, Gyro_y, Gyro_z;

float gyroX_offset = 0, gyroY_offset = 0, gyroZ_offset = 0;

void MPU6050_setSampleRate(uint8_t rate) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(SMPLRT_DIV);
    I2C_Write(rate);
    I2C_Stop();
}

void MPU6050_setClockSource(uint8_t source) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(PWR_MGMT_1);
    I2C_Write(source);
    I2C_Stop();
}

void MPU6050_setGyroConfig(uint8_t range) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(GYRO_CONFIG);
    I2C_Write(range);
    I2C_Stop();
}

void MPU6050_setAccelConfig(uint8_t range) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(ACCEL_CONFIG);
    I2C_Write(range);
    I2C_Stop();
}

void MPU6050_setInterruptEnable(uint8_t enable) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(INT_ENABLE);
    I2C_Write(enable);
    I2C_Stop();
}

void MPU6050_setLPF(uint8_t range) {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(CONFIG);
    I2C_Write(range);
    I2C_Stop();
}

void MPU6050_init() {
    _delay_ms(150); // Power-up time >100ms

    MPU6050_setSampleRate(0x07); // Set sample rate to 1kHz
    MPU6050_setClockSource(0x00); // Internal Clock
    MPU6050_setGyroConfig(0x08); // Full scale range ±500°/s
    MPU6050_setAccelConfig(0x10); // ±8g
    MPU6050_setLPF(0x03); // Configure low pass filter if exists
    MPU6050_setInterruptEnable(0x01); // Enable interrupts
    
}

void MPU_Start_Loc() {
    I2C_Start_Wait(MPU_ADDRESS);
    I2C_Write(ACCEL_XOUT_H);
    I2C_Repeated_Start(MPU_ADDRESS_READ);
}

void Read_RawValue(float acc[3], float gyro[3]) {
    MPU_Start_Loc();
    
    // Store accelerometer readings in acc array
    acc[0] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack(); // Acc_x
    acc[1] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack(); // Acc_y
    acc[2] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack(); // Acc_z
    
    // Skip Temperature reading
    float dummy = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack();

    // Store gyroscope readings in gyro array
    gyro[0] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack(); // Gyro_x
    gyro[1] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack(); // Gyro_y
    gyro[2] = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Nack(); // Gyro_z

    I2C_Stop();
}

void MPU6050_calibrate(float gyro_offset[3]) {
    const int num_samples = 1000;
    long gyro_total[3] = {0, 0, 0}; // Temporary variables for summing gyro values

    for (int i = 0; i < num_samples; i++) {
        float acc[3], gyro[3];
        Read_RawValue(acc, gyro); // Read raw values into arrays
        
        gyro_total[0] += gyro[0];
        gyro_total[1] += gyro[1];
        gyro_total[2] += gyro[2];
        _delay_ms(3); // Small delay between samples
    }

    // Calculate average offsets
    gyro_offset[0] = gyro_total[0] / num_samples;
    gyro_offset[1] = gyro_total[1] / num_samples;
    gyro_offset[2] = gyro_total[2] / num_samples;
}



