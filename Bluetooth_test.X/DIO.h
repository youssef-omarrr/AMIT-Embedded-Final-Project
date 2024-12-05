// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DIO_H
#define	DIO_H

#include<avr/io.h>


#define A 0
#define B 1
#define C 2
#define D 3

#define OUT 1
#define IN 0

#define HIGH 1
#define LOW 0

#define ON 1
#define OFF 0

#include <xc.h> // include processor files - each processor file is guarded.  

/**
 * 
 * @param portName
 * @param status
 * @return void
 */
void setPort_dir(char portName, char status);
/**
 * 
 * @param portName
 * @param pinNum
 * @param status
 * @return void
 */
void setPIN_dir(char portName,char pinNum, char status);
/**
 * 
 * @param portName
 * @param val
 * @param status
 * @return void
 */
void setPort_dirVal(char portName,char val,char status);
/**
 * 
 * @param portName
 * @param pinNum
 * @param status
 * @return void
 */
void setPIN(char portName,char pinNum ,char status);
/**
 * 
 * @param portName
 * @return char
 */
char readPort(char portName);
/**
 * 
 * @param portName
 * @param pinNum
 * @return char
 */
char readPIN(char portName, char pinNum );


char readPIN(char portName, char pinNum );
void reverse(char s[]);
void itoa(int n, char s[]);
#endif	/* DIO_H */