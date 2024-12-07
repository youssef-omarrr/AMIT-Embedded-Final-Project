#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "MY_MPU.h"
#include "MY_UART.h"
#include "mpu_i2c.h"
#include "My_TimerCounter.h"
#include "frame_formatter.h"

static int counter = 0;
char frame[15] = {'A'};

ISR(TIMER2_OVF_vect) {
    counter++;
    if (counter >= 62) {
        uart_send_str(frame);
        counter = 0;
    }
}

int main(void) {
    
    // Initialize communication
    init_uart(ASYN, 9600);
    I2C_Init();
    
    //     Initialize sensor data arrays
    float acc[3] = {0};
    float gyro[3] = {0};
    float gyro_offset[3] = {0};

    // Initialize angle state
    AngleState angle_state;
    initAngleState(&angle_state);

    // Initialize and calibrate MPU6050
    MPU6050_init();
    MPU6050_calibrate(gyro_offset);

    // Initialize timer for 1MS intervals for integration
    init_Timer0_WithOCR0(CTC_MODE, TIMER0_MC_CLK_64, 124);
    
    // Initialize timer for UART sending ISR every second 
    initNormalMode_Timer_Counter2(TIMER2_MC_CLK_1024);
    
    sei();
    
    while (1) {
        // Read raw values from the MPU
        Read_RawValue(acc, gyro);
        // Update the angles and store it in frame
        updateAngles(&angle_state, acc, gyro, gyro_offset);
        // pre-prepare the frame for UART sending
        formatSignalMsg(&angle_state, frame);
        Timer0_waitCTC();
    }
}