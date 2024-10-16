/* The register map is provided at
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] deg/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(deg/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81 m/s^2)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/

#ifndef MPU6050_LIGHT_H
#define MPU6050_LIGHT_H

#include <stdint.h>
#include <stdbool.h>
#include <mI2C.h>

// MPU6050 configuration constants
#define MPU6050_ADDR                  0x68
#define MPU6050_SMPLRT_DIV_REGISTER   0x19
#define MPU6050_CONFIG_REGISTER       0x1a
#define MPU6050_GYRO_CONFIG_REGISTER  0x1b
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1c
#define MPU6050_PWR_MGMT_1_REGISTER   0x6b

#define MPU6050_GYRO_OUT_REGISTER     0x43
#define MPU6050_ACCEL_OUT_REGISTER    0x3B

#define RAD_2_DEG             57.29578 // [deg/rad]
#define CALIB_OFFSET_NB_MES   500
#define TEMP_LSB_2_DEGREE     340.0    // [bit/celsius]
#define TEMP_LSB_OFFSET       12412.0

#define DEFAULT_GYRO_COEFF    0.98

// Struct to hold MPU6050 data and configuration
typedef struct {
    uint8_t address;
    float gyro_lsb_to_degsec, acc_lsb_to_g;
    float gyroXoffset, gyroYoffset, gyroZoffset;
    float accXoffset, accYoffset, accZoffset;
    float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
    float angleAccX, angleAccY;
    float angleX, angleY, angleZ;
    unsigned long preInterval;
    float filterGyroCoef;
    bool upsideDownMounting;
} MPU6050;

// MPU CONFIG SETTER
uint8_t MPU6050_setGyroConfig(MPU6050 *mpu, int config_num);
uint8_t MPU6050_setAccConfig(MPU6050 *mpu, int config_num);

// MPU CONFIG GETTER
float MPU6050_getGyroXoffset(MPU6050 *mpu);
float MPU6050_getGyroYoffset(MPU6050 *mpu);
float MPU6050_getGyroZoffset(MPU6050 *mpu);

float MPU6050_getAccXoffset(MPU6050 *mpu);
float MPU6050_getAccYoffset(MPU6050 *mpu);
float MPU6050_getAccZoffset(MPU6050 *mpu);

float MPU6050_getFilterGyroCoef(MPU6050 *mpu);
float MPU6050_getFilterAccCoef(MPU6050 *mpu);

// DATA GETTER
float MPU6050_getTemp(MPU6050 *mpu);

float MPU6050_getAccX(MPU6050 *mpu);
float MPU6050_getAccY(MPU6050 *mpu);
float MPU6050_getAccZ(MPU6050 *mpu);

float MPU6050_getGyroX(MPU6050 *mpu);
float MPU6050_getGyroY(MPU6050 *mpu);
float MPU6050_getGyroZ(MPU6050 *mpu);

float MPU6050_getAccAngleX(MPU6050 *mpu);
float MPU6050_getAccAngleY(MPU6050 *mpu);

float MPU6050_getAngleX(MPU6050 *mpu);
float MPU6050_getAngleY(MPU6050 *mpu);
float MPU6050_getAngleZ(MPU6050 *mpu);

// INLOOP UPDATE
void MPU6050_fetchData(MPU6050 *mpu); 
void MPU6050_update(MPU6050 *mpu);


#endif
