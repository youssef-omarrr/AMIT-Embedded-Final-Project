#include "motor_driver.h"
#include "DIO.h"
#include "mtimer.h"

void init_motor() {
    //init timer0 amd timer2
    timer0_OC0_init();
    initTimer0(TIMER_FAST_PWM, CLK01_64); // Fast PWM, clock prescaler 64
    timer0_OC0_selectMode(OC0_FPWM_CLEAR); // Non-inverted PWM
    OCR0 = 128; // Set duty cycle (50%)

    timer2_OC2_init();
    initTimer2(TIMER_FAST_PWM, CLK2_64); // Fast PWM, clock prescaler 64
    timer2_OC2_selectMode(OC2_FPWM_CLEAR); // Non-inverted PWM
    OCR2 = 128; // Set duty cycle (50%)

    //set the control pins as output
    setPINC_dir(MOTOR_LEFT_IN1, OUT);
    setPINC_dir(MOTOR_LEFT_IN2, OUT);

    setPINC_dir(MOTOR_RIGHT_IN1, OUT);
    setPINC_dir(MOTOR_RIGHT_IN2, OUT);

    //set enable pin as output
//    setPIND_dir(MOTOR_LEFT_EN, OUT);
//    setPINB_dir(MOTOR_RIGHT_EN, OUT);

    //set initial state of motors as stopped
    setPINC(MOTOR_LEFT_IN1, LOW);
    setPINC(MOTOR_LEFT_IN2, LOW);

    setPINC(MOTOR_RIGHT_IN1, LOW);
    setPINC(MOTOR_RIGHT_IN2, LOW);
}

void move_forward(int* pSpeed) {

    // Set speed (PWM values)
    OCR2 = *pSpeed; // Set PWM for left motor
    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate forward
    setPINC(MOTOR_LEFT_IN1, HIGH);
    setPINC(MOTOR_LEFT_IN2, LOW);

    // Right motor: rotate forward
    setPINC(MOTOR_RIGHT_IN1, HIGH);
    setPINC(MOTOR_RIGHT_IN2, LOW);

}

void move_backward(int* pSpeed) {

    // Set speed (PWM values)
    OCR2 = *pSpeed; // Set PWM for left motor
    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate backward
    setPINC(MOTOR_LEFT_IN1, LOW);
    setPINC(MOTOR_LEFT_IN2, HIGH);

    // Right motor: rotate backward
    setPINC(MOTOR_RIGHT_IN1, LOW);
    setPINC(MOTOR_RIGHT_IN2, HIGH);

}

void move_right(int* pSpeed) {

    // Set speed (PWM values)
    OCR2 = *pSpeed; // Set PWM for left motor
    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate forward
    setPINC(MOTOR_LEFT_IN1, HIGH);
    setPINC(MOTOR_LEFT_IN2, LOW);

    // Right motor: rotate backward
    setPINC(MOTOR_RIGHT_IN1, LOW);
    setPINC(MOTOR_RIGHT_IN2, HIGH);


}

void move_left(int* pSpeed) {
    // Set speed (PWM values)
    OCR2 = *pSpeed; // Set PWM for left motor
    OCR0 = *pSpeed; // Set PWM for right motor

    // Left motor: rotate backward
    setPINC(MOTOR_LEFT_IN1, LOW);
    setPINC(MOTOR_LEFT_IN2, HIGH);

    // Right motor: rotate forward
    setPINC(MOTOR_RIGHT_IN1, HIGH);
    setPINC(MOTOR_RIGHT_IN2, LOW);

}

void stop_motor() {
    setPINC(MOTOR_LEFT_IN1, LOW);
    setPINC(MOTOR_LEFT_IN2, LOW);
    setPINC(MOTOR_RIGHT_IN1, LOW);
    setPINC(MOTOR_RIGHT_IN2, LOW);

    // Set PWM values to 0 to stop motors
    OCR2 = 0;
    OCR0 = 0;
}