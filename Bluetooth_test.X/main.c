#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MY_UART.h"
#include "LCD_4.h"
#include "motor_driver.h"

// Constants
#define MPU_DATA_MAX_LEN     20

// Structure to hold motor control data

typedef struct {
    char direction;
    uint8_t speed;
} MotorData_t;

// functions used in parse function

static int find_char_after(const char *str, char target, int start_pos) {
    int i = start_pos;
    while (str[i] != '\0') {
        if (str[i] == target) {
            return i;
        }
        i++;
    }
    return -1;
}

//to get the speed from the string and turn it into integer

static int extract_number(const char *str, int start_pos) {
    int result = 0;
    int i = start_pos;

    //loop until a number is found
    while (str[i] != '\0' && (str[i] < '0' || str[i] > '9')) {
        i++;
    }

    // turn the number to an integer
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

// parsing the data (getting the data between brackets)

static uint8_t parse_mpu_data(const char *data, MotorData_t * motor_data) {

    int dir_start = find_char_after(data, '(', 0); //after the first '(' lies the dir
    if (dir_start >= 0) {// error handling
        char direction = data[dir_start + 1];
//                LCD4_CLEAR();
//                LCD4_WRITE(direction);

        int speed_pos = find_char_after(data, '(', dir_start + 1); // after the second '('
        if (speed_pos >= 0) {// error handling
            int speed = extract_number(data, speed_pos + 1);
//                        LCD4_WRITE_NUM(speed);

            if (direction == 'W' || direction == 'S' ||
                direction == 'A' || direction == 'D') { // bt2aked en ely wasal 7aga mn wasd
                LCD4_WRITE('Z');
                //el speed mapped hena ha
                if (speed < 30) speed = 0;
                if (speed > 255) speed = 255;

                motor_data->direction = direction;
                motor_data->speed = (uint8_t) speed;
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    init_uart(ASYN, 9600);
    init_LCD4();
    init_motor();
    LCD4_CLEAR();

    MotorData_t motorData;
    char mpu_data[MPU_DATA_MAX_LEN] = "";
    char temp[1];
    while (1) {
        temp[0] = uart_receive_data();
        LCD4_WRITE(temp[0]);
        strcat(mpu_data, temp);

        if (temp[0] == '>') {
//            LCD4_CLEAR();
//            LCD4_SWRITE(mpu_data);
            if (parse_mpu_data(mpu_data, &motorData)) {

                //print direction and speed on LCD
                LCD4_CLEAR();
                LCD4_SWRITE("Data parsed: ");
                LCD4_WRITE(motorData.direction);
                LCD4_SetCursor(0, 1);
                LCD4_SWRITE("Speed: ");
                LCD4_WRITE_NUM(motorData.speed);

                switch (motorData.direction) {
                    //forward
                case 'W':
                    move_forward(motorData.speed);
                    break;
                    //backward
                case 'S':
                    move_backward(motorData.speed);
                    break;
                    //left
                case 'A':
                    move_left(motorData.speed);
                    break;
                    //right
                case 'D':
                    move_right(motorData.speed);
                    break;
                default:
                    stop_motor();
                    break;
                }


                //                LCD4_CLEAR();
            }
            strcpy(mpu_data, "");
        }
    }
    return 0;
}