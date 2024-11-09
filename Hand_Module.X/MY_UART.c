#define F_CPU 16000000UL 

#include<avr/io.h>
#include"MY_UART.h"
#include "DIO.h"
#include<util/delay.h>
#include"int_to_arr.h"


//void BaudRate_X2_U();

void Set_XCK_DIR(char Generation_dir) {

    switch (Generation_dir) {

        case Slave_clk:
            setPIN_dir(B, XCK, IN);
            break;

        case Master_clk:
            setPIN_dir(B, XCK, OUT);
            break;

        default:
            break;


    }

}

void WAIT_UNTIL_UDRisNOT_EMPTY() {

    while (!(UCSRA & (1 << UDRE)));

}

void WAIT_UNTIL_RX_ALL_SHIFTED() {

    while (!(UCSRA & (1 << RXC)));
   
}

void UDREF_INT_EN() {

    UCSRB |= (1 << UDRIE);

}

void RXF_INT_EN() {

    UCSRB |= (1 << RXCIE);

}

void Set_StopBitsNum_U(char StopBitsNum) {

    switch (StopBitsNum) {

        case _1Sbit:
            UCSRC |= (UCSRC | (1 << URSEL)) & (~(1 << USBS));
            break;

        case _2Sbit:
            UCSRC |= ((1 << URSEL) | (1 << USBS));
            break;

        default:
            break;

    }

}

void SetBaudRate_U(int BaudRate) {


    UBRRL = BaudRate;
    UBRRH = (BaudRate >> 8);

}
//void SetDataSize_U(char size);


//void SetParityMode_U(char Parity);

void RX_TX_MODE(char RX_TX) {

    UCSRB |= (RX_TX << 3);

}

void init_UART_Async(int BaudRate, char StopBits, char RX_or_TX) {

    short temp = (F_CPU / 16.0 / BaudRate) - 1;

    Set_StopBitsNum_U(StopBits);
    _delay_us(5);

    SetBaudRate_U(temp);
    _delay_us(5);

    //    SetParityMode_U(Parity);
    //    _delay_us(5);

    //    SetDataSize_U(size);
    //    _delay_us(5);

    RX_TX_MODE(RX_or_TX);
    _delay_us(5);

    RXF_INT_EN();

}

void init_UART_Sync(int BaudRate, char StopBits, char RX_or_TX, char Generation_dir) {

    short temp = (F_CPU / 2.0 / BaudRate) - 1;

    Set_StopBitsNum_U(StopBits);
    _delay_us(5);

    SetBaudRate_U(temp);
    _delay_us(5);

    //    SetParityMode_U(Parity);
    //    _delay_us(5);

    //    SetDataSize_U(size);
    //    _delay_us(5);

    RX_TX_MODE(RX_or_TX);
    _delay_us(5);

    Set_XCK_DIR(Generation_dir);
    _delay_us(5);

    RXF_INT_EN();

}

void UART_SEND(char data) {

    UCSRA &= ~(1 << TXC);

    WAIT_UNTIL_UDRisNOT_EMPTY();

    UDR = data;

}

void UART_SEND_STR(char* str) {

    for (int i = 0; str[i] != '\0'; i++) {
        UART_SEND(str[i]);
//        _delay_ms(5);
    }

}

char UART_RECEIVE() {
    
    char status;

    WAIT_UNTIL_RX_ALL_SHIFTED();
    
    status =UCSRA;
    
    if(status & ((1<<FE)|(1<<DOR)|(1<<2))) 
        return -1;

    return UDR;

}

void UART_SEND_NUM(int num){
    
    char c[11];
    
    itoa(num,c);
    
    UART_SEND_STR(c);
    
}

