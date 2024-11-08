#include "MY_MPU.h"
#include "myI2C.h"
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

void Read_RawValue() {
    MPU_Start_Loc();
    Acc_x = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack();
    Acc_y = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack();
    Acc_z = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack();
    Temperature = ((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack();

    Gyro_x = (((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack());
    Gyro_y = (((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Ack());
    Gyro_z = (((int) I2C_Read_Ack() << 8) | (int) I2C_Read_Nack());

    I2C_Stop();
}

void MPU6050_calibrate() {
    const int num_samples = 1000;
    long gyroX_total = 0, gyroY_total = 0, gyroZ_total = 0;

    for (int i = 0; i < num_samples; i++) {
        Read_RawValue();
        gyroX_total += Gyro_x;
        gyroY_total += Gyro_y;
        gyroZ_total += Gyro_z;
        _delay_ms(3); // small delay between samples
    }

    // Calculate average offsets
    gyroX_offset = gyroX_total / num_samples;
    gyroY_offset = gyroY_total / num_samples;
    gyroZ_offset = gyroZ_total / num_samples;
}


