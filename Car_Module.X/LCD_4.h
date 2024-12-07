// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MY_LCD4_H
#define	MY_LCD4_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include<avr/io.h>

#define LCD_DATA_DIR DDRA
#define LCD_DATA PORTA

#define LCD_CONTROL PORTB
#define LCD_CONTROL_DIR DDRB

#define RS PB1
#define RW PB2
#define EN PB3

#define RET_HOME 0x02
#define _8Bits_Mode 0x38
#define _4Bits_Mode 0x28
#define CLR 0x01
#define CUR_OFF_DISP_ON 0x0C
#define Entry_Mode 0x06
#define MOVE_RIGHT  0x14
#define MOVE_LEFT   0x10

void LCD4_CMD(char);
void init_LCD4();
void LCD4_WRITE(char);
void LCD4_CLEAR();
void LCD4_SWRITE(char*);
void LCD4_WRITE_NUM(int);
void LCD4_MOVE_RIGHT(char steps);
void LCD4_MOVE_LEFT(char steps);
void LCD4_SetCursor(char row , char col);


#endif	/* MY_LCD4_H */
