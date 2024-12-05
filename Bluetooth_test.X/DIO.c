#include"DIO.h"
#include "string.h"
#include<avr/io.h>

/**
 * 
 * @param portName
 * @param status
 * @return void
 */
void setPort_dir(char portName, char status) {

    switch (portName) {

    case A:

        switch (status) {

        case IN:
            DDRA = 0;
            break;

        case OUT:
            DDRA = 0xFF;
            break;

        default:
            break;

        }
        break;

    case B:

        switch (status) {

        case IN:
            DDRB = 0;
            break;

        case OUT:
            DDRB = 0xFF;
            break;

        default:
            break;
        }
        break;
    case C:

        switch (status) {

        case IN:
            DDRC = 0;
            break;

        case OUT:
            DDRC = 0xFF;
            break;

        default:
            break;

        }
        break;
    case D:

        switch (status) {

        case IN:
            DDRD = 0;
            break;

        case OUT:
            DDRD = 0xFF;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

}

/**
 * 
 * @param pinNum
 * @param status
 * @return void
 */
void setPIN_dir(char portName, char pinNum, char status) {

    switch (portName) {

    case A:

        switch (status) {

        case IN:
            DDRA &= ~(1 << pinNum);
            break;

        case OUT:
            DDRA |= (1 << pinNum);
            break;

        default:
            break;

        }
        break;

    case B:

        switch (status) {

        case IN:
            DDRB &= ~(1 << pinNum);
            break;

        case OUT:
            DDRB |= (1 << pinNum);
            break;

        default:
            break;
        }
        break;
    case C:

        switch (status) {

        case IN:
            DDRC &= ~(1 << pinNum);
            break;

        case OUT:
            DDRC |= (1 << pinNum);
            break;

        default:
            break;

        }
        break;
    case D:

        switch (status) {

        case IN:
            DDRD &= ~(1 << pinNum);
            break;

        case OUT:
            DDRD |= (1 << pinNum);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

}

/**
 * 
 * @param portName
 * @param val
 * @return void
 */
void setPort_dirVal(char portName, char val, char status) {

    switch (portName) {

    case A:

        switch (status) {

        case IN:
            DDRA &= ~(val);
            break;

        case OUT:
            DDRA |= (val);
            break;

        default:
            break;

        }
        break;

    case B:

        switch (status) {

        case IN:
            DDRB &= ~(val);
            break;

        case OUT:
            DDRB |= (val);
            break;

        default:
            break;
        }
        break;
    case C:

        switch (status) {

        case IN:
            DDRC &= ~(val);
            break;

        case OUT:
            DDRC |= (val);
            break;

        default:
            break;

        }
        break;
    case D:

        switch (status) {

        case IN:
            DDRD &= ~(val);
            break;

        case OUT:
            DDRD |= (val);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void setPIN(char portName, char pinNum, char status) {

    switch (portName) {

    case A:

        switch (status) {

        case LOW:
            PORTA &= ~(1 << pinNum);
            break;

        case HIGH:
            PORTA |= (1 << pinNum);
            break;

        default:
            break;

        }
        break;

    case B:

        switch (status) {

        case LOW:
            PORTB &= ~(1 << pinNum);
            break;

        case HIGH:
            PORTB |= (1 << pinNum);
            break;

        default:
            break;
        }
        break;
    case C:

        switch (status) {

        case LOW:
            PORTC &= ~(1 << pinNum);
            break;

        case HIGH:
            PORTC |= (1 << pinNum);
            break;

        default:
            break;

        }
        break;
    case D:

        switch (status) {

        case LOW:
            PORTD &= ~(1 << pinNum);
            break;

        case HIGH:
            PORTD |= (1 << pinNum);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

/**
 * 
 * @param portName
 * @return char
 */
char readPort(char portName) {

    switch (portName) {

    case A:
        return PINA;

    case B:
        return PINB;

    case C:
        return PINC;

    case D:
        return PIND;

    default:
        break;
    }
    return 0;
}

/**
 * 
 * @param portName
 * @param pinNum
 * @return char
 */
char readPIN(char portName, char pinNum) {

    switch (portName) {

    case A:
        return PINA & (1 << pinNum);

    case B:
        return PINB & (1 << pinNum);

    case C:
        return PINC & (1 << pinNum);

    case D:
        return PIND & (1 << pinNum);

    default:
        break;
    }
    return 0;

}

void togglePIN(char portName, char pinNum) {

    switch (portName) {

    case A:
        PORTA ^= (1 << pinNum);
        break;

    case B:
        PORTB ^= (1 << pinNum);
        break;

    case C:
        PORTC ^= (1 << pinNum);
        break;

    case D:
        PORTD ^= (1 << pinNum);
        break;

    default:
        break;
    }
}


