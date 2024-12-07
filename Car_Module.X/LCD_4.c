
#define F_CPU 16000000UL
#define _OPEN_SYS_ITOA_EXT

#include"LCD_4.h"
#include<util/delay.h>
#include"DIO.h"



void LCD4_EN() {

    LCD_CONTROL |= (1 << EN);
    _delay_ms(5);
    LCD_CONTROL &= ~(1 << EN);
}

void LCD4_CMD(char cmd) {

    //set RS to 0
    LCD_CONTROL &= ~(1 << RS);
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0);
    LCD4_EN();
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd << 4);
    LCD4_EN();

    _delay_ms(20);

}

void LCD4_CLEAR() {
    
    LCD_CONTROL &= ~(1 << RS);
    LCD_DATA = (LCD_DATA & 0x0F) | (CLR & 0xF0);
    LCD4_EN();
    LCD_DATA = (LCD_DATA & 0x0F) | (CLR << 4);
    LCD4_EN();

    _delay_ms(5);
    
}

void init_LCD4() {

    //DIO

    setPort_dirVal(A, 0xF0, OUT);
    setPort_dirVal(B, ((1 << RS) | (1 << RW) | (1 << EN)), OUT);
    
    _delay_ms(20);

    //LCD setup
    setPIN(B, (1 << RW), LOW); //write mode
    //Return Home
    LCD4_CMD(RET_HOME);
    //set mode
    LCD4_CMD(_4Bits_Mode);
    //set cursor and display
    LCD4_CMD(CUR_OFF_DISP_ON);
    //CLEAR
    LCD4_CLEAR();
    //entry mode
    //LCD4_CMD(Entry_Mode);



}

void LCD4_WRITE(char data) {

    _delay_ms(10);
    LCD_CONTROL |= (1 << RS);
    LCD_DATA = (LCD_DATA & 0x0F) | (data & 0xF0);
    LCD4_EN();
    LCD_DATA = (LCD_DATA & 0x0F) | (data << 4);
    LCD4_EN();
    
    _delay_ms(20);
}

void LCD4_SWRITE(char* str) {

    for (int i = 0; str[i] != '\0'; i++) {
        LCD4_WRITE(str[i]);
    }

}

void LCD4_WRITE_NUM(int num) {

    char str[11];
    itoa(num, str);
    LCD4_SWRITE(str);

}
void LCD4_MOVE_LEFT(char steps){
    for(int  i = 0; i < steps; ++i){
        LCD4_CMD(MOVE_LEFT);   
    }
}

void LCD4_MOVE_RIGHT(char steps){
        for(int  i = 0; i < steps; ++i){
        LCD4_CMD(MOVE_RIGHT);   
    }
}

void LCD4_SetCursor(char row , char col){
 
    LCD4_CMD(0x80|col|(row<<6));
    
}