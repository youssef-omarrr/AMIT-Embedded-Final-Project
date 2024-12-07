#define F_CPU 16000000UL

// All header files are saved here
#include "mHEADERS.h"

// Constants
#define MPU_DATA_MAX_LEN     20

// Structure to hold motor control data
typedef struct {
    char direction;
    uint8_t speed;
} MotorData_t;


int main(void) {
    // init functions
    init_uart(ASYN, 9600);
    init_LCD4();
    init_motor();
    LCD4_CLEAR();

    // init variables to store motor data
    MotorData_t motorData;
    char mpu_data[MPU_DATA_MAX_LEN] = "";
    char temp[1];

    while (1) {
        // variable to store each new char from MPU 
        temp[0] = uart_receive_data();
        // variable to store the whole data packet in this form : <(direction)(speed)>
        strcat(mpu_data, temp);

        /*  <(direction)(speed)>
         * < : start bit
         * 
         * (direction) : a char where:
         * 'w': forward
         * 'a': left
         * 's': backward
         * 'd': right
         * 
         * (speed) : an int from 0:255
         * 
         * > : end bit
         */

        // testing
        // LCD4_WRITE(temp[0]);

        // wait till start bit
        if (temp[0] == '>') {

            // parse data to get direction and speed
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
            }
            strcpy(mpu_data, "");
        }
    }
    return 0;
}