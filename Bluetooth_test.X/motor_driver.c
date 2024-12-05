#include "motor_driver.h"
#include "DIO.h"
#include "mtimer.h"

void init_motor() {
    //init timer0 amd timer2:
    
//    timer0_OC0_init();
//    initTimer0(TIMER_FAST_PWM, CLK01_64); // Fast PWM, clock prescaler 64
//    timer0_OC0_selectMode(OC0_FPWM_CLEAR); // Non-inverted PWM
//    OCR0 = 128; // Set duty cycle (50%)

    timer2_OC2_init();
    initTimer2(TIMER_FAST_PWM, CLK2_64); // Fast PWM, clock prescaler 64
    
    timer2_OC2_selectMode(OC2_FPWM_CLEAR); // Non-inverted PWM
    OCR2 = 128; // Set duty cycle (50%)
    

    //set the control pins as output
    setPIN_dir(C,MOTOR_LEFT_IN1, OUT);
    setPIN_dir(C,MOTOR_LEFT_IN2, OUT);

    setPIN_dir(C,MOTOR_RIGHT_IN1, OUT);
    setPIN_dir(C,MOTOR_RIGHT_IN2, OUT);

    //set initial state of motors as stopped
    setPIN(C,MOTOR_LEFT_IN1, LOW);
    setPIN(C,MOTOR_LEFT_IN2, LOW);

    setPIN(C,MOTOR_RIGHT_IN1, LOW);
    setPIN(C,MOTOR_RIGHT_IN2, LOW);
}

void move_forward(int Speed) {

    // Set speed (PWM values)
      OCR2 = Speed; // Set PWM for left motor
//    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate forward
    setPIN(C,MOTOR_LEFT_IN1, HIGH);
    setPIN(C,MOTOR_LEFT_IN2, LOW);

    // Right motor: rotate forward
    setPIN(C,MOTOR_RIGHT_IN1, HIGH);
    setPIN(C,MOTOR_RIGHT_IN2, LOW);

}

void move_backward(int Speed) {

    // Set speed (PWM values)
    OCR2 = Speed; // Set PWM for left motor
//    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate backward
    setPIN(C,MOTOR_LEFT_IN1, LOW);
    setPIN(C,MOTOR_LEFT_IN2, HIGH);

    // Right motor: rotate backward
    setPIN(C,MOTOR_RIGHT_IN1, LOW);
    setPIN(C,MOTOR_RIGHT_IN2, HIGH);

}

void move_right(int Speed) {

    // Set speed (PWM values)
    OCR2 =  Speed; // Set PWM for left motor
//    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate forward
    setPIN(C,MOTOR_LEFT_IN1, HIGH);
    setPIN(C,MOTOR_LEFT_IN2, LOW);

    // Right motor: rotate backward
    setPIN(C,MOTOR_RIGHT_IN1, LOW);
    setPIN(C,MOTOR_RIGHT_IN2, HIGH);


}

void move_left(int Speed) {
    // Set speed (PWM values)
    OCR2 = Speed; // Set PWM for left motor
//    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate backward
    setPIN(C,MOTOR_LEFT_IN1, LOW);
    setPIN(C,MOTOR_LEFT_IN2, HIGH);

    // Right motor: rotate forward
    setPIN(C,MOTOR_RIGHT_IN1, HIGH);
    setPIN(C,MOTOR_RIGHT_IN2, LOW);

}

void stop_motor() {
    setPIN(C,MOTOR_LEFT_IN1, LOW);
    setPIN(C,MOTOR_LEFT_IN2, LOW);
    setPIN(C,MOTOR_RIGHT_IN1, LOW);
    setPIN(C,MOTOR_RIGHT_IN2, LOW);

    // Set PWM values to 0 to stop motors
    OCR2 = 0;
//    OCR0 = 0;
}
