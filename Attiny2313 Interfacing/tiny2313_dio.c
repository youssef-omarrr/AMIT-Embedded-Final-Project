#include "tiny2313_dio.h"
#include <xc.h>

void setPortBDirection(char mask, char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRB |= mask; // Set bits to output
            break;
        case DIRECTION_IN:
            DDRB &= ~mask; // Clear bits to input
            break;
    }
}


void setPinBDirection(char pinNum, char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRB |= (1 << pinNum); // Set pin to output
            break;
        case DIRECTION_IN:
            DDRB &= ~(1 << pinNum); // Set pin to input
            break;
    }
}


void setAllPortBDirection(char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRB = 0xFF; // Set all pins to output
            break;
        case DIRECTION_IN:
            DDRB = 0x00; // Set all pins to input
            break;
    }
}


void setPinBState(char pinNum, char state) {
    switch (state) {
        case STATE_HIGH:
            PORTB |= (1 << pinNum); // Set pin high
            break;
        case STATE_LOW:
            PORTB &= ~(1 << pinNum); // Set pin low
            break;
    }
}


void setAllPortBState(char state) {
    switch (state) {
        case STATE_HIGH:
            PORTB = 0xFF; // Set all pins high
            break;
        case STATE_LOW:
            PORTB = 0x00; // Set all pins low
            break;
    }
}


char readPortB() {
    return PINB; // Return the current state of PORT B
}


char readPinB(char pinNum) {
    return (PINB & (1 << pinNum)) ? STATE_HIGH : STATE_LOW; // Return the state of the pin
}

// PORT D


void setPortDDirection(char mask, char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRD |= mask; // Set bits to output
            break;
        case DIRECTION_IN:
            DDRD &= ~mask; // Clear bits to input
            break;
    }
}


void setPinDDirection(char pinNum, char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRD |= (1 << pinNum); // Set pin to output
            break;
        case DIRECTION_IN:
            DDRD &= ~(1 << pinNum); // Set pin to input
            break;
    }
}


void setAllPortDDirection(char direction) {
    switch (direction) {
        case DIRECTION_OUT:
            DDRD = 0xFF; // Set all pins to output
            break;
        case DIRECTION_IN:
            DDRD = 0x00; // Set all pins to input
            break;
    }
}


void setPinDState(char pinNum, char state) {
    switch (state) {
        case STATE_HIGH:
            PORTD |= (1 << pinNum); // Set pin high
            break;
        case STATE_LOW:
            PORTD &= ~(1 << pinNum); // Set pin low
            break;
    }
}


void setAllPortDState(char state) {
    switch (state) {
        case STATE_HIGH:
            PORTD = 0xFF; // Set all pins high
            break;
        case STATE_LOW:
            PORTD = 0x00; // Set all pins low
            break;
    }
}


char readPortD() {
    return PIND; // Return the current state of PORT D
}


char readPinD(char pinNum) {
    return (PIND & (1 << pinNum)) ? STATE_HIGH : STATE_LOW; // Return the state of the pin
}
