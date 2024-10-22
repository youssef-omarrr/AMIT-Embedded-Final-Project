#include "motor_driver.h"
#include "DIO.h"
#include "mtimer.h"

void init_motor(){
    //init timer0 amd timer2
    timer0_OC0_init();
    initTimer0(TIMER_FAST_PWM, CLK01_64); // Fast PWM, clock prescaler 64
    timer0_OC0_selectMode(OC0_FPWM_CLEAR); // Non-inverted PWM
    OCR0 = 128;  // Set duty cycle (50%)
    
    timer2_OC2_init();
    initTimer2(TIMER_FAST_PWM, CLK2_64); // Fast PWM, clock prescaler 64
    timer2_OC2_selectMode(OC2_FPWM_CLEAR); // Non-inverted PWM
    OCR2 = 128;  // Set duty cycle (50%)
    
    //set the control pins as output
    setPINB_dir(MOTOR_LEFT_IN1,  OUT);
    setPINB_dir(MOTOR_LEFT_IN2,  OUT);
    
    setPIND_dir(MOTOR_RIGHT_IN1, OUT);
    setPIND_dir(MOTOR_RIGHT_IN2, OUT);
    
    //set enable pin as output
    setPINB_dir(MOTOR_LEFT_EN,  OUT);
    setPIND_dir(MOTOR_RIGHT_EN, OUT);
    
    //set initial state of motors as stopped
    setPINB(MOTOR_LEFT_IN1, LOW);
    setPINB(MOTOR_LEFT_IN2, LOW);
    
    setPIND(MOTOR_RIGHT_IN1, LOW);
    setPIND(MOTOR_RIGHT_IN2, LOW);
}


void move_forward(int* x, int* y) {
    // Left motor: rotate forward
    setPINB(MOTOR_LEFT_IN1, HIGH);
    setPINB(MOTOR_LEFT_IN2, LOW);
    
    // Right motor: rotate forward
    setPIND(MOTOR_RIGHT_IN1, HIGH);
    setPIND(MOTOR_RIGHT_IN2, LOW);
    
    // Set speed (PWM values)
    OCR2 = *x;  // Set PWM for left motor
    OCR0 = *y;  // Set PWM for right motor
}

void move_backward(int* x, int* y) {
    // Left motor: rotate backward
    setPINB(MOTOR_LEFT_IN1, LOW);
    setPINB(MOTOR_LEFT_IN2, HIGH);
    
    // Right motor: rotate backward
    setPIND(MOTOR_RIGHT_IN1, LOW);
    setPIND(MOTOR_RIGHT_IN2, HIGH);
    
    // Set speed (PWM values)
    OCR2 = *x;  // Set PWM for left motor
    OCR0 = *y;  // Set PWM for right motor
}

void move_right(int* x, int* y) {
    // Left motor: rotate forward
    setPINB(MOTOR_LEFT_IN1, HIGH);
    setPINB(MOTOR_LEFT_IN2, LOW);
    
    // Right motor: rotate backward
    setPIND(MOTOR_RIGHT_IN1, LOW);
    setPIND(MOTOR_RIGHT_IN2, HIGH);
    
    // Set speed (PWM values)
    OCR2 = *x;  // Set PWM for left motor
    OCR0 = *y;  // Set PWM for right motor
}

void move_left(int* x, int* y) {
    // Left motor: rotate backward
    setPINB(MOTOR_LEFT_IN1, LOW);
    setPINB(MOTOR_LEFT_IN2, HIGH);
    
    // Right motor: rotate forward
    setPIND(MOTOR_RIGHT_IN1, HIGH);
    setPIND(MOTOR_RIGHT_IN2, LOW);
    
    // Set speed (PWM values)
    OCR2 = *x;  // Set PWM for left motor
    OCR0 = *y;  // Set PWM for right motor
}
