/* 
 * File:   TWI.h
 *
 * Created on October 22, 2024, 11:06 PM
 */

#ifndef TWI_H
#define	TWI_H

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>
#include "tiny2313_dio.h"

#define PIN_SDA 				PB5
#define PIN_SCL 				PB7

#define WAIT_LONG				5 // 4,7us
#define WAIT_SHORT 				4 // 4,0us

// USISR mask
#define USISR_CLOCK_8_BITS		0b11110000
#define USISR_CLOCK_1_BIT  		0b11111110


// Function prototypes
void set_SCL_High();
void set_SDA_High();
void set_SCL_Low();
void set_SDA_Low();
void wait_SCL_High();

// TWI/I2C functions
void TWI_init();
void TWI_send_start();
void TWI_send_stop();
unsigned char TWI_transfer(unsigned char usisr_mask);
unsigned char TWI_write_byte(unsigned char data);
unsigned char TWI_read_byte(unsigned char nack);

#endif	/* TWI_H */

