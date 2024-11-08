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
#ifndef MY_UART_H
#define	MY_UART_H

//data size 
#define _5bits 0
#define _6bits 1
#define _7bits 2
#define _8bits 3
#define _9bits 7

//number of stop bits
#define _1Sbit 0
#define _2Sbit 1

//Parity Mode
#define NO_PARITY   0
#define EVEN_PARITY 2
#define ODD_PARITY  3

//Clk Mode
#define Async 0
#define Sync  1

//Baud Rates
#define BaudRate_9600   9600
#define BaudRate_115200 115200
#define BaudRate_2400   2400
#define BaudRate_1200   1200

//communication mode
#define FULL_DUPLEX_UART   3
#define TRANSMIT_ONLY_UART 1
#define RECIEVE_ONLY_UART  2

//master-slave clock generation
#define Master_clk          1
#define Slave_clk           2

#define XCK PB0

#include <xc.h> // include processor files - each processor file is guarded.  

void init_UART_Async(int BaudRate,char stopBits ,char RX_or_TX);
void init_UART_Sync(int BaudRate,char stopBits ,char RX_or_TX,char Generation_dir);
//void BaudRate_X2_U();
char WAIT_UNTIL_UDRisNOT_EMPTY();
//void UDREF_INT_EN();
//void RXF_INT_EN();
void Set_StopBitsNum_U(char StopBitsNum);
void SetBaudRate_U(int BaudRate);
//void SetDataSize_U(char size);
//void SetParityMode_U(char Parity);
void RX_TX_MODE(char RX_TX);
void UART_SEND(char data);
void UART_SEND_STR(char*);
char WAIT_UNTIL_RX_ALL_SHIFTED();
char UART_RECEIVE();
void Set_XCK_DIR(char Generation_dir);

void UART_SEND_NUM(int num);

#endif	/* MY_UART_H */

