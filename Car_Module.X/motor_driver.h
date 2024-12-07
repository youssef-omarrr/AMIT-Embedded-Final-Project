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
#define MOTOR_LEFT_IN1   PC3  // Left motor IN1 pin
#define MOTOR_LEFT_IN2   PC4  // Left motor IN2 pin
#define MOTOR_LEFT_EN    PD7  // Left motor enable pin (OC2 for timer 2 output)

// Right Motor Controls
#define MOTOR_RIGHT_IN1  PC5  // Right motor IN1 pin
#define MOTOR_RIGHT_IN2  PC6  // Right motor IN2 pin
#define MOTOR_RIGHT_EN   PD7  // for now i will use timer2 only to use the lcd              ~(Right motor enable pin (OC0 for timer 0 output))

void init_motor();
void move_forward  (int Speed);
void move_backward (int Speed);
void move_right    (int Speed);
void move_left     (int Speed);
void stop_motor();

#endif	/* MOTOR_DRIVER_H */