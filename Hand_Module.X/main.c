#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "MY_MPU.h"
#include "MY_UART.h"
#include "mpu_i2c.h"
#include "My_TimerCounter.h"

// Function to format and send angle data over UART for Debugging
static void sendAngleData(const AngleState* state) {
    char buffer[30];
    sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n", 
            state->angles[X], 
            state->angles[Y], 
            state->angles[Z]);
    UART_SEND_STR(buffer);
}

int main(void) {
    // Initialize communication
    init_UART_Async(BaudRate_9600, _1Sbit, TRANSMIT_ONLY_UART);
    I2C_Init();

    // Initialize sensor data arrays
    float acc[3] = {0};
    float gyro[3] = {0};
    float gyro_offset[3] = {0};

    // Initialize angle state
    AngleState angle_state;
    initAngleState(&angle_state);

    // Initialize and calibrate MPU6050
    MPU6050_init();
    MPU6050_calibrate(gyro_offset);

    // Initialize timer for 1ms intervals
    init_Timer0_WithOCR0(CTC_MODE, TIMER0_MC_CLK_64, 124);

    while (1) {
        Read_RawValue(acc, gyro);
        updateAngles(&angle_state, acc, gyro, gyro_offset);
        sendAngleData(&angle_state);
        Timer0_waitCTC();
    }
}