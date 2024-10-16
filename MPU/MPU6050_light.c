#include "MPU6050_light.h";

//for I2C lma nb2a n3ml el library
// #include <Wire.h> 

/* Wrap an angle in the range [-limit,+limit] (special thanks to Edgar Bonet!) */
static float wrap(float angle,float limit){
  while (angle >  limit) angle -= 2*limit;
  while (angle < -limit) angle += 2*limit;
  return angle;
}

/* INIT and BASIC FUNCTIONS */

// Initializes the MPU6050 structure
void MPU6050_init(MPU6050 *mpu, uint8_t address) {
    mpu->address = address;
    mpu->gyro_lsb_to_degsec = 131.0;
    mpu->acc_lsb_to_g = 16384.0;
    mpu->gyroXoffset = mpu->gyroYoffset = mpu->gyroZoffset = 0;
    mpu->accXoffset = mpu->accYoffset = mpu->accZoffset = 0;
    mpu->filterGyroCoef = DEFAULT_GYRO_COEFF;
    mpu->upsideDownMounting = false;
}

// Sets gyro configuration
uint8_t MPU6050_setGyroConfig(MPU6050 *mpu, int config_num) {
    // Initialize TWI with the MPU6050 address
    initTWI(mpu->address); 
    // Send the config register address
    TWI_MTX(mpu->address, MPU6050_CONFIG_REGISTER); 
    // Send the configuration value
    TWI_MTX(mpu->address, config_num); 
    return 0; // Modify this to return a status code if needed
}

// Sets accelerometer configuration
uint8_t MPU6050_setAccConfig(MPU6050 *mpu, int config_num) {
    // Initialize TWI with the MPU6050 address
    initTWI(mpu->address); 
    // Send sample rate divisor register address
    TWI_MTX(mpu->address, MPU6050_SMPLRT_DIV_REGISTER); 
    // Send the configuration value
    TWI_MTX(mpu->address, config_num); 
    return 0; // Modify this to return a status code if needed
}

// Update the MPU6050 angles
void MPU6050_update(MPU6050 *mpu) {
    MPU6050_fetchData(mpu);

    // Simple placeholder logic for angle update
    mpu->angleAccX = (mpu->accX / mpu->acc_lsb_to_g) * 57.2958;  // Convert to degrees
    mpu->angleAccY = (mpu->accY / mpu->acc_lsb_to_g) * 57.2958;
}

// Fetches raw data from the sensor
void MPU6050_fetchData(MPU6050 *mpu) {
    char buffer[14]; // Buffer to hold the data

    initTWI(mpu->address); // Initialize TWI with the MPU6050 address
    TWI_MTX(mpu->address, 0x3B); // Write the base address for accelerometer readings

    // Read the incoming data (accX, accY, accZ, temp, gyroX, gyroY, gyroZ)
    if (TWI_MRX_buf(mpu->address, buffer, 14) == 0) { // Request 14 bytes of data
        mpu->accX =  (buffer[0] << 8)  | buffer[1];
        mpu->accY =  (buffer[2] << 8)  | buffer[3];
        mpu->accZ =  (buffer[4] << 8)  | buffer[5];
        mpu->temp =  (buffer[6] << 8)  | buffer[7];
        mpu->gyroX = (buffer[8] << 8)  | buffer[9];
        mpu->gyroY = (buffer[10] << 8) | buffer[11];
        mpu->gyroZ = (buffer[12] << 8) | buffer[13];
    }
}

// Getters for individual data fields
float MPU6050_getAccX (MPU6050 *mpu) { return mpu->accX; }
float MPU6050_getAccY (MPU6050 *mpu) { return mpu->accY; }
float MPU6050_getAccZ (MPU6050 *mpu) { return mpu->accZ; }
float MPU6050_getTemp (MPU6050 *mpu) { return mpu->temp; }
float MPU6050_getGyroX(MPU6050 *mpu) { return mpu->gyroX; }
float MPU6050_getGyroY(MPU6050 *mpu) { return mpu->gyroY; }
float MPU6050_getGyroZ(MPU6050 *mpu) { return mpu->gyroZ; }