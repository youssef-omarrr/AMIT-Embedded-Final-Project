/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

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
/**
 * 
 * @param portName
 * @param pinNum
 */
void togglePIN(char portName,char pinNum);
// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation


#endif	/* DIO_H */

