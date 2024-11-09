#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "MY_MPU.h"
#include "MY_UART.h"

#define FREQ        250   // Sampling frequency                                                                                                   
#define SSF_GYRO    65.5  // Sensitivity Scale Factor of the gyro from datasheet                                                                  
#define PI  3.14

void formatAndSendUARTData(float Xa, float Ya, float Za, float t, float Xg, float Yg, float Zg) {
    char buffer[20];

    sprintf(buffer, " Ax = %.2f g\t", Xa);
    UART_SEND_STR(buffer);

    sprintf(buffer, " Ay = %.2f g\t", Ya);
    UART_SEND_STR(buffer);

    sprintf(buffer, " Az = %.2f g\t", Za);
    UART_SEND_STR(buffer);

    sprintf(buffer, " T = %.2f°C\t", t);
    UART_SEND_STR(buffer);

    sprintf(buffer, " Gx = %.2f deg/s\t", Xg);
    UART_SEND_STR(buffer);

    sprintf(buffer, " Gy = %.2f deg/s\t", Yg);
    UART_SEND_STR(buffer);

    sprintf(buffer, " Gz = %.2f deg/s\r\n", Zg);
    UART_SEND_STR(buffer);
}

float angleX = 0, angleY = 0, angleZ = 0;
float gyro_angleX = 0, gyro_angleY = 0, gyro_angleZ = 0;
float acc_angleX = 0, acc_angleY = 0, acc_angleZ = 0;

void updateAngles(float acc[3], float gyro[3], float gyro_offset[3]) {
    // Adjust gyroscope readings by offset
    float Xg = gyro[0] - gyro_offset[0];
    float Yg = gyro[1] - gyro_offset[1];
    float Zg = gyro[2] - gyro_offset[2];

    // Integrate gyro rate to get angle (degrees)
    gyro_angleX += (Xg / (FREQ * SSF_GYRO));
    gyro_angleY += (-Yg / (FREQ * SSF_GYRO));

    // Compensate for IMU yaw
    gyro_angleY += gyro_angleX * sin(gyro[2] * (PI / (FREQ * SSF_GYRO * 180)));
    gyro_angleX -= gyro_angleY * sin(gyro[2] * (PI / (FREQ * SSF_GYRO * 180)));

    // Calculate total 3D acceleration vector
    float acc_total_vector = sqrt(pow(acc[0], 2) + pow(acc[1], 2) + pow(acc[2], 2));

    if (fabs(acc[0]) < acc_total_vector) {
        acc_angleX = asin((float) acc[1] / acc_total_vector) * (180 / PI);
    }
    if (fabs(acc[1]) < acc_total_vector) {
        acc_angleY = asin((float) acc[0] / acc_total_vector) * (180 / PI);
    }

    // Complementary filter
    gyro_angleX = gyro_angleX * 0.9996 + acc_angleX * 0.0004;
    gyro_angleY = gyro_angleY * 0.9996 + acc_angleY * 0.0004;

    // Final angles with smoothing
    angleX = angleX * 0.9 + gyro_angleX * 0.1;
    angleY = angleY * 0.9 + gyro_angleY * 0.1;
    angleZ = -gyro[2] / SSF_GYRO;
}

int main(void) {
    init_UART_Async(BaudRate_9600, _1Sbit, TRANSMIT_ONLY_UART);
    I2C_Init();
    float acc[3] = {0, 0, 0}; // Accelerometer values
    float gyro[3] = {0, 0, 0}; // Gyroscope values
    float gyro_offset[3] = {0, 0, 0}; // Gyroscope offsets

    // Initialize MPU6050
    MPU6050_init();

    // Calibrate gyroscope
    MPU6050_calibrate(gyro_offset);

    while (1) {
        Read_RawValue(acc, gyro); // Read values into acc and gyro arrays
        updateAngles(acc, gyro, gyro_offset); // Update angles based on current readings and offset
        // Send calibrated and integrated gyro angles over UART
        char buffer[30];
        sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n", angleX, angleY, angleZ);
        UART_SEND_STR(buffer);

    }
}