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

void formatSignalMsg(const AngleState* state, char* frame) {
    char direction;
    int speed;
    float absX = fabs(state->angles[X]);
    float absY = fabs(state->angles[Y]);

    // Determine primary direction based on largest angle
    if (absX > absY) {
        // Forward/Backward movement
        direction = (state->angles[X] > 0) ? 'W' : 'S';
        speed = (int) ((absX * 255) / 90.0);
    } else {
        // Left/Right movement
        direction = (state->angles[Y] > 0) ? 'D' : 'A'; // Assuming +Y is right tilt
        speed = (int) ((absY * 255) / 90.0);
    }

    // Clamp speed between 0 and 255
    speed = (speed > 255) ? 255 : (speed < 0) ? 0 : speed;

    // Format the message
    sprintf(frame, "-(%c)(%d)-", direction, speed);
}

int main(void) {
    // Initialize communication
    init_UART_Async(BaudRate_9600, _1Sbit, TRANSMIT_ONLY_UART);
    I2C_Init();

    // Initialize sensor data arrays
    float acc[3] = {0};
    float gyro[3] = {0};
    float gyro_offset[3] = {0};
    char frame[15];
    // Initialize angle state
    AngleState angle_state;
    initAngleState(&angle_state);

    // Initialize and calibrate MPU6050
    MPU6050_init();
    MPU6050_calibrate(gyro_offset);

    // Initialize timer for 1ms intervals
    init_Timer0_WithOCR0(CTC_MODE, TIMER0_MC_CLK_64, 124);
    int counter = 0;

    while (1) {
        Read_RawValue(acc, gyro);
        updateAngles(&angle_state, acc, gyro, gyro_offset);
        //        sendAngleData(&angle_state);
        formatSignalMsg(&angle_state, frame);
        if (++counter % 2) {
            UART_SEND_STR(frame);
        }
        Timer0_waitCTC();
    }
}