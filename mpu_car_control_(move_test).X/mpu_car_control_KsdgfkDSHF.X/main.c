#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "freertos/include/FreeRTOS.h"
#include "freertos/include/FreeRTOSConfig.h"
#include "freertos/include/task.h"
#include "freertos/include/queue.h"
#include "DIO.h"
#include "mI2C.h"
#include "mtimer.h"
#include "mUART.h"
#include "motor_driver.h"

// Structure to hold motor control data
typedef struct {
    char direction;
    uint8_t speed;
} MotorData_t;

// Function declarations
static void MPU_Task(void *pvParameters);
static void Motor_Task(void *pvParameters);
static void init_hardware(void);

// Global handles
static QueueHandle_t xMotorQueue = NULL;

// Constants
#define MOTOR_QUEUE_LENGTH    3    // Reduced queue length
#define MOTOR_TASK_STACK     128   // Reduced stack size
#define MPU_TASK_STACK       128   // Reduced stack size
#define MPU_DATA_MAX_LEN     50

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


// parsing the data
static uint8_t parse_mpu_data(const char *data, MotorData_t *motor_data) {
    if (!data || !motor_data) return 0;
    
    int dir_start = find_char_after(data, '(', 0);//after the first '(' lies the dir
    if (dir_start >= 0) {// error handling
        char direction = data[dir_start + 1];
        
        int speed_pos = find_char_after(data, '(', dir_start + 1);// after the second '('
        if (speed_pos >= 0) {// error handling
            int speed = extract_number(data, speed_pos + 1);
            
            if (direction == 'w' || direction == 's' || 
                direction == 'a' || direction == 'd') { // bt2aked en ely wasal 7aga mn wasd
                
                //el speed mapped hena ha
                if (speed < 0) speed = 0;
                if (speed > 100) speed = 100;
                
                motor_data->direction = direction;
                motor_data->speed = (uint8_t)speed;
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
        SPH = (uint8_t)((RAMEND) >> 8);
        SPL = (uint8_t)(RAMEND);
    #endif

    init_hardware();
    
    // Create queue
    xMotorQueue = xQueueCreate(MOTOR_QUEUE_LENGTH, sizeof(MotorData_t));
    if (xMotorQueue == NULL) {
        UART_sen_str("Queue creation failed\r\n");
    }
    
    UART_sen_str("Queue created successfully\r\n");

    // Create tasks
    if (xTaskCreate(MPU_Task, "MPU", MPU_TASK_STACK, NULL, 2, NULL) != pdPASS) {
        UART_sen_str("MPU task creation failed\r\n");
    }
    
    if (xTaskCreate(Motor_Task, "Motor", MOTOR_TASK_STACK, NULL, 1, NULL) != pdPASS) {
        UART_sen_str("Motor task creation failed\r\n");
    }
    
    UART_sen_str("Tasks created successfully\r\n");
    
    vTaskStartScheduler();

    return 0;
}

static void init_hardware(void) {
    initUART(9600, TRANSMITTER, ASYNCH);
    init_motor();
}

static void MPU_Task(void *pvParameters) {
    MotorData_t motorData;
    char mpu_data[MPU_DATA_MAX_LEN];
    
    // Initial delay to allow system to stabilize
    vTaskDelay(pdMS_TO_TICKS(100));
    
    UART_sen_str("MPU Task started\r\n");

    while (1) {
        // Simulate MPU data eb2a 4ylha we 7ot el data ely gaya mn el MPU ya magd
        // bnafs el format ha
        strcpy(mpu_data, "dir(w) , speed(100)");
        
        if (parse_mpu_data(mpu_data, &motorData)) {
            UART_sen_str("Data parsed: ");//momken t4yl kol el uart send str ana 7atethom 34an atest
            UART_send(motorData.direction);
            UART_sen_str("\r\n");
            
            // Try to send to queue with timeout
            if (xQueueSend(xMotorQueue, (void *)&motorData, pdMS_TO_TICKS(100)) == pdPASS) {
                UART_sen_str("Data sent to queue\r\n");
            } else {
                UART_sen_str("Queue send failed\r\n");
            }
        } else {
            UART_sen_str("Parse failed\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(20));// el tasks hattkarar kol 20 clock tick m4 kol ma t8yar el etgah ya3ny 5ly balek
                                      // bas keda keda el delay s8ayar fa el mafrod n7es enha btet8yar 3ala tol
    }
}

static void Motor_Task(void *pvParameters) {
    MotorData_t receivedData;
    uint8_t mappedSpeed;
    
    // Initial delay to allow system to stabilize
    vTaskDelay(pdMS_TO_TICKS(100));
    
    UART_sen_str("Motor Task started\r\n");

    while (1) {
        if (xQueueReceive(xMotorQueue, &receivedData, pdMS_TO_TICKS(100)) == pdPASS) {
            UART_sen_str("Data received\r\n");
            
            mappedSpeed = (receivedData.speed * 255) / 100;
            
            switch (receivedData.direction) {
                case 'w':
                    move_forward(&mappedSpeed);
                    UART_sen_str("Forward\r\n");
                    break;
                case 's':
                    move_backward(&mappedSpeed);
                    UART_sen_str("Backward\r\n");
                    break;
                case 'a':
                    move_left(&mappedSpeed);
                    UART_sen_str("Left\r\n");
                    break;
                case 'd':
                    move_right(&mappedSpeed);
                    UART_sen_str("Right\r\n");
                    break;
                default:
                    stop_motor();
                    UART_sen_str("Stop\r\n");
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}