/* 
 * File:   motor_driver.h
 * Author: User
 *
 * Created on October 22, 2024, 1:48 PM
 */

#ifndef MOTOR_DRIVER_H
#define	MOTOR_DRIVER_H

#include <avr/io.h>

// Left Motor Controls
#define MOTOR_LEFT_IN1   PB1  // Left motor IN1 pin
#define MOTOR_LEFT_IN2   PB2  // Left motor IN2 pin
#define MOTOR_LEFT_EN    PB3  // Left motor enable pin (OC2 for timer 2 output)

// Right Motor Controls
#define MOTOR_RIGHT_IN1  PD4  // Right motor IN1 pin
#define MOTOR_RIGHT_IN2  PD5  // Right motor IN2 pin
#define MOTOR_RIGHT_EN   PD7  // Right motor enable pin (OC0 for timer 0 output)

void init_motor();
void move_forward  (int* x, int* y);
void move_backward (int* x, int* y);
void move_right    (int* x, int* y);
void move_left     (int* x, int* y);
void stop_motor();

#endif	/* MOTOR_DRIVER_H */

