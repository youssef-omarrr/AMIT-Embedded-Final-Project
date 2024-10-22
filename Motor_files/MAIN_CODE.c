#include <avr/io.h>
#include <stdio.h>
#include "mHEADERS.h"
#include "MPU6050_light.h"
#include "motor_driver.h"


//init function declaration
void MPU_func();
void Motor_func(void* para);

//init functions handlers
TaskHandle_t MPU_handler   = NULL;
TaskHandle_t Motor_handler = NULL;

//init semaphore
SemaphoreHandle_t semph_handle;

//data that will store MPU reading in format: "x(number), y(number), dir(char)"
char* data = NULL;

int main() {
    //init uart for testing
    initUART(9600, TRANSMITTER, ASYNCH);
    
    // Create the binary semaphore
    semph_handle = xSemaphoreCreateBinary();

    // Give the semaphore so that the first task can take it
    xSemaphoreGive(semph_handle);
    
    //init tasks
    xTaskCreate(MPU_func,   "MPU_task",   100, NULL,         1, &MPU_handler);
    xTaskCreate(Motor_func, "Motor_task", 100, (void*) data, 1, &Motor_handler);
    
    //start Scheduler
    vTaskStartScheduler();
    
    while (1) {

    }
    return 0;
}

///////////////// --------- tasks functions ----------///////////////////
void MPU_func(){
    vTaskDelay(10);
    while (1) {
        /* See if we can obtain the semaphore. If the semaphore is not
           available wait 10 ticks to see if it becomes free. */
        if (xSemaphoreTake(semph_handle, (TickType_t) 10) == pdTRUE) {
            //--- write code here ---//
            
            
            //take reading from attiny
            char* test_input = "x(200), y(100)"
            
            //add reading to global data variable
            data = test_input
            
            
            
            //--- write code here ---//
            /* We have finished accessing the shared resource. Release the
               semaphore. */
            xSemaphoreGive(semph_handle);
            taskYIELD(); // Allow other tasks to run
        } //if
    }//while
}//function


void Motor_func(void* data){
    vTaskDelay(10);
    while (1) {
        /* See if we can obtain the semaphore. If the semaphore is not
           available wait 10 ticks to see if it becomes free. */
        if (xSemaphoreTake(semph_handle, (TickType_t) 10) == pdTRUE) {
            //--- write code here ---//

            //split data
            int x, y;
            char dir;
            sscanf(data, "x(%d), y(%d), dir(%c)", &x, &y, &dir);
            
            //OCR2 range -> 0:255
            /* write logic to choose in which direction we will move
             *  
                move_forward (&x, &y);
                move_backward(&x, &y);
                move_right   (&x, &y);
                move_left    (&x, &y);
             * 
             */
            
            
            
          
            //--- write code here ---//
            /* We have finished accessing the shared resource. Release the
               semaphore. */
            xSemaphoreGive(semph_handle);
            taskYIELD(); // Allow other tasks to run
        } //if
    }//while
}//function

///////////////// --------- tasks functions ----------///////////////////
