/* 
 * File:   my_usart.h
 * Author: Lenovo
 *
 * Created on September 6, 2024, 6:09 PM
 */

#ifndef MY_USART_H
#define	MY_USART_H

#include <avr/io.h>

#define F_CPU             16000000UL
#include <util/delay.h>


//CLOCK MODES
#define ASYN                    0
#define DOUBLE_SPD_ASYN         1
#define MASTER_SYN              2
#define SLAVE_SYN               3

#define XCK                     PB0


void init_uart(char clk_mode, int baud);
void uart_send_char(char data);
void uart_send_str(char *pData);
char uart_receive_data();
void uart_send_num(int num);
#endif	/* MY_USART_H */