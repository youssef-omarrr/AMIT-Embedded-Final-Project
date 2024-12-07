#ifndef FORMATTER_H
#define FORMATTER_H

#include <math.h>
#include <stdio.h>
#include "MY_MPU.h"
#include "MY_UART.h"
// Function declarations

/**
 * @brief Sends angle data over UART in a formatted manner for debugging.
 *
 * @param state Pointer to the AngleState structure containing angle data.
 */
void sendAngleData(const AngleState* state);

/**
 * @brief Formats a control signal message based on angles and speed.
 *
 * @param state Pointer to the AngleState structure containing angle data.
 * @param frame Pointer to a buffer where the formatted message will be stored.
 *              The buffer must be large enough to hold the formatted string.
 */
void formatSignalMsg(const AngleState* state, char* frame);

#endif // MY_MPU_H