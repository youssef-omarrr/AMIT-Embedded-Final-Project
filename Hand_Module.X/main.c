/*
 * File:   main.c
 * Author: yousefmahmoud
 *
 * Created on November 4, 2024, 9:56 PM
 */
#define F_CPU 16000000UL


#include <avr/io.h>
#include<util/delay.h>
#include <stdio.h>
#include <stdlib.h>  // Required for abs function

#include"MY_MPU.h"
#include"/Users/yousefmahmoud/Desktop/Studying/Embedded_Diploma_AMIT/EmbeddedC_codes/1/app1.X/MY_UART.h"

int main(void) {

    float angleY, angleX;
    int speedX, speedY;
    char signX = '+', signY = '+';
    char data[15];

    init_UART_Async(BaudRate_9600, _1Sbit, TRANSMIT_ONLY_UART);

    init_MPU();
    _delay_ms(50);

    while (1) {

        angleX = get_angle_x();
        angleY = get_angle_y();

        if (angleX < 0)
            signX = '-';

        if (angleY < 0)
            signY = '-';

        speedX = (int) ((abs(angleX) * 255) / 90.0);
        speedY = (int) ((abs(angleY) * 255) / 90.0);

        sprintf(data, "x(%c%d),y(%c%d)", signX, speedX, signY, speedY);

        UART_SEND_STR(data);

    }
}
