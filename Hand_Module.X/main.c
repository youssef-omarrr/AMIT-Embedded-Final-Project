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

void updateAngles() {
    // Gyroscope sensitivity scale factor: 131 LSB/(°/s) for ±250°/s range
    float Xg = Gyro_x - gyroX_offset;
    float Yg = Gyro_y - gyroY_offset;
    float Zg = Gyro_z - gyroZ_offset;

    // Integrate gyro rate to get angle (degrees)
    gyro_angleX += (Xg / (FREQ * SSF_GYRO));
    gyro_angleY += (-Yg / (FREQ * SSF_GYRO));

    // Transfer roll to pitch if IMU has yawed                                                                                                      
    gyro_angleY += gyro_angleX * sin(Gyro_z * (PI / (FREQ * SSF_GYRO * 180)));
    gyro_angleX -= gyro_angleY * sin(Gyro_z * (PI / (FREQ * SSF_GYRO * 180)));

    // Calculate total 3D acceleration vector : ?(X² + Y² + Z²)                                                                                     
    float acc_total_vector = sqrt(pow(Acc_x, 2) + pow(Acc_y, 2) + pow(Acc_z, 2));

    // To prevent asin to produce a NaN, make sure the input value is within [-1;+1]                                                                
    if (fabs(Acc_x) < acc_total_vector) {
        acc_angleX = asin((float) Acc_y / acc_total_vector) * (180 / PI); // asin gives angle in radian. Convert to degree multiplying by 180/pi
    }

    if (fabs(Acc_y) < acc_total_vector) {
        acc_angleY = asin((float) Acc_x / acc_total_vector) * (180 / PI);
    }



    gyro_angleX = gyro_angleX * 0.9996 + acc_angleX * 0.0004;
    gyro_angleY = gyro_angleY * 0.9996 + acc_angleY * 0.0004;



    angleX = angleX* 0.9 + gyro_angleX * 0.1;
    angleY = angleY * 0.9 + gyro_angleY * 0.1;
    angleZ = -Gyro_z / SSF_GYRO; // Store the angular motion for this axis                                                            

}

int main(void) {
    init_UART_Async(BaudRate_9600, _1Sbit, TRANSMIT_ONLY_UART);
    I2C_Init();
    MPU6050_init();
    MPU6050_calibrate();

    while (1) {
        Read_RawValue();
        updateAngles();

        // Send calibrated and integrated gyro angles over UART
        char buffer[30];
        sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n", angleX, angleY, angleZ);
        UART_SEND_STR(buffer);

    }
}