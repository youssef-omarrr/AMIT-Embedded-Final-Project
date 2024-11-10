#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "MY_MPU.h"
#include "MY_UART.h"
#include "mpu_i2c.h"
#include "My_TimerCounter.h"

#define FREQ        1000   // Sampling frequency                                                                                                   
#define SSF_GYRO    65.5  // Sensitivity Scale Factor of the gyro from datasheet                                                                  
#define PI  3.14

#define X  0
#define Y  1
#define Z  2

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
    float Xg = gyro[X] - gyro_offset[X];
    float Yg = gyro[Y] - gyro_offset[Y];
    float Zg = gyro[Z] - gyro_offset[Z];

    // Integrate gyro rate to get angle (degrees)
    gyro_angleX += (Xg / (FREQ * SSF_GYRO)); //Calculate the traveled pitch angle
    gyro_angleY += (Yg / (FREQ * SSF_GYRO)); //Calculate the traveled roll angle

    // If the IMU has yawed(Rotated Around Z) transfer the roll angle to the pitch angel
    // and pitch to roll angle
    gyro_angleY += gyro_angleX * sin(gyro[Z] * (PI / (FREQ * SSF_GYRO * 180)));
    gyro_angleX -= gyro_angleY * sin(gyro[Z] * (PI / (FREQ * SSF_GYRO * 180)));

    // Calculate total 3D acceleration vector
    float acc_total_vector = sqrt((acc[X] * acc[X]) + (acc[Y] * acc[Y]) + (acc[Z] * acc[Z]));

    if (fabs(acc[X]) < acc_total_vector) {
        acc_angleX = asin((float) acc[Y] / acc_total_vector) * (180 / PI);
    }
    if (fabs(acc[Y]) < acc_total_vector) {
        acc_angleY = asin((float) acc[X] / acc_total_vector) * (180 / PI);
    }

    // Complementary filter
    gyro_angleX = gyro_angleX * 0.96 + acc_angleX * 0.04;
    gyro_angleY = gyro_angleY * 0.96 + acc_angleY * 0.04;

    // Final angles with smoothing
    angleX = angleX * 0.7 + gyro_angleX * 0.3;
    angleY = angleY * 0.7 + gyro_angleY * 0.3;
    angleZ = -Zg / (FREQ * SSF_GYRO);
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

    init_Timer0_WithOCR0(CTC_MODE, TIMER0_MC_CLK_64, 124); // init timer with 124 to achive 1ms timer
    while (1) {
        Read_RawValue(acc, gyro); // Read values into acc and gyro arrays

        updateAngles(acc, gyro, gyro_offset); // Update angles based on current readings and offset

        // Send calibrated and integrated gyro angles over UART

        char buffer[30];
        sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n", angleX, angleY, angleZ);
        UART_SEND_STR(buffer);

        Timer0_waitCTC();

    }
}