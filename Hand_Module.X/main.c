#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include <avr/interrupt.h>
#include "MY_MPU.h"
#include "MY_UART.h"
#include "mpu_i2c.h"
#include "My_TimerCounter.h"

static int counter = 0;
char frame[15] = {'A'};

ISR(TIMER2_OVF_vect){
    counter++;
    if (counter >= 62){
        uart_send_str(frame);
        counter = 0;
    }
}


// Function to format and send angle data over UART for Debugging

static void sendAngleData(const AngleState* state) {
    char buffer[30];
    sprintf(buffer, "X Angle: %.2f\tY Angle: %.2f\tZ Angle: %.2f\r\n",
        state->angles[X],
        state->angles[Y],
        state->angles[Z]);
    uart_send_str(buffer);
}

void formatSignalMsg(const AngleState* state, char* frame) {
    char direction;
    int speed;
    float absX = fabs(state->angles[X]);
    float absY = fabs(state->angles[Y]);

    // Determine primary direction based on largest angle
    if (absX > absY) {
        direction = (state->angles[X] > 0) ? 'W' : 'S'; // Forward/Backward
        speed = (int) ((absX * 255) / 90.0);
    } else {
        direction = (state->angles[Y] > 0) ? 'D' : 'A'; // Right/Left
        speed = (int) ((absY * 255) / 90.0);
    }

    // Clamp speed to the range [0, 255]
    if (speed > 255) speed = 255;
    if (speed < 0) speed = 0;

    // Manually construct the frame string
    char speed_str[4]; // Enough to hold "255" + null terminator
    int i = 0;

    // Add "<("
    frame[i++] = '<';
    frame[i++] = '(';

    // Add direction
    frame[i++] = direction;

    // Add ")("
    frame[i++] = ')';
    frame[i++] = '(';

    // Convert speed to string manually
    int temp_speed = speed;
    int digits = 0;
    do {
        digits++;
        temp_speed /= 10;
    } while (temp_speed > 0);

    for (int j = digits - 1; j >= 0; j--) {
        speed_str[j] = (speed % 10) + '0';
        speed /= 10;
    }
    speed_str[digits] = '\0'; // Null-terminate the string

    // Append speed to the frame
    for (int j = 0; speed_str[j] != '\0'; j++) {
        frame[i++] = speed_str[j];
    }

    // Add ")>"
    frame[i++] = ')';
    frame[i++] = '>';

    // Null-terminate the frame string
    frame[i] = '\0';
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

    //  initAngleState(&angle_state);

    // Initialize and calibrate MPU6050
    MPU6050_init();
    MPU6050_calibrate(gyro_offset);

    // Initialize timer for 1ms intervals
    init_Timer0_WithOCR0(CTC_MODE, TIMER0_MC_CLK_64, 124);
    
    initNormalMode_Timer_Counter2(TIMER2_MC_CLK_1024);
    TWCR &= ~(1<<TWIE);
    sei();
    while (1) {
        Read_RawValue(acc, gyro);
        updateAngles(&angle_state, acc, gyro, gyro_offset);
        formatSignalMsg(&angle_state, frame);
        Timer0_waitCTC();
    }
}