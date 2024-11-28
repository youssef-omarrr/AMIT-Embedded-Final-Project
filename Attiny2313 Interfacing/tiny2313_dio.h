/* 
 * File:   tiny2313_dio.h
 * Created on October 22, 2024, 00:04 PM
 */

#ifndef TINY2313_DIO_H
#define	TINY2313_DIO_H


#include <xc.h>


// Direction constants
#define DIRECTION_OUT  1
#define DIRECTION_IN   0

// State constants
#define STATE_HIGH     1
#define STATE_LOW      0


// Like the ATmega32, each port in the ATtiny4313 has three main registers: PORTx, DDRx, and PINx.
// - PORTx: Controls the output state of the port pins when configured as outputs. 
//          It can also be used to enable or disable the internal pull-up resistors when the pins are configured as inputs.
//
// - DDRx: Defines the data direction of the pins.
//
// - PINx: Used to read the logic level of the port pins. This register is read-only.

// To enable the internal pull-up resistor on a pin, you must:
// 1. Configure the pin as an input.
// 2. Set the corresponding bit in the PORTx register to enable the pull-up resistor.

// To disable the pull-up resistor on a pin, you can either:
// - Clear the corresponding bit in the PORTx register.
// - Reconfigure the pin as an output.

// Additionally, setting the PUD (Pull-up Disable) bit in the MCUCR register globally disables all pull-up resistors on all ports, regardless of the PORTx settings.



// To avoid unintended glitches or brief voltage spikes on the pin, 
// it is essential to use intermediate steps when rapidly changing a pin's configuration.
// When switching between input and output high, an intermediate step of 
// setting the pin to output low ({DDxn, PORTxn} = 0b10) must occur first.
// Similarly, when switching between input with pull-up and output low, 
// the pin should first be set to input ({DDxn, PORTxn} = 0b00) before switching to output low.

// Port A <==  Won't be used as it accepts XTAL1,2 and RESET

/*
 * PORT B:
 *  _______________________________________________________________________
 * | Pin  | Alternate Function   | Description                             |
 * |------|----------------------|-----------------------------------------|
 * | PB0  |         AIN0         | Analog Comparator                       |
 * | PB1  |         AIN1         | Analog Comparator                       |
 * | PB2  |         OC0A         | Timer0 Compare Match A                  |
 * | PB3  |         OC1A         | Timer1 Compare Match A                  |
 * | PB4  |         OC1B         | Timer1 Compare Match B                  |
 * | PB5  |       DI,  SDA       | USI Data Input, I2C Data                |
 * | PB6  |          DO          | USI Data Output                         |
 * | PB7  |      USCK, SCL       | USI Clock, I2C CLOCK                    |
 * |_______________________________________________________________________| 
 */
 
/* 
 *  PORT D:
 *  _______________________________________________________________________
 * | Pin  | Alternate Function   | Description                             |
 * |------|----------------------|-----------------------------------------|
 * | PD0  |         RXD          | UART Data Receiver                      |
 * | PD1  |         TXD          | UART Data Transmitter                   |
 * | PD2  |      INT0, XCk       | External Interrupt 0, USART Clock       |
 * | PD3  |         INT1         | External Interrupt 1                    |
 * | PD4  |          T0          | Timer0 Clock                            |
 * | PD5  |       T1,  OC0B      | Timer1 Clock, Timer0 Compare Match B    |
 * | PD6  |         ICP          | Timer1 Input Capture Pin                |
 * |_______________________________________________________________________|
 */



/**
 * @brief Set the direction of multiple pins on PORT B.
 *
 * @param mask The bitmask for the pins to be configured.
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setPortBDirection(char mask, char direction) ;

/**
 * @brief Set the direction of a single pin on PORT B.
 *
 * @param pinNum The pin number (0-7).
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setPinBDirection(char pinNum, char direction) ;

/**
 * @brief Set all pins on PORT B to a specific direction.
 *
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setAllPortBDirection(char direction);

/**
 * @brief Set the state of a specific pin on PORT B.
 *
 * @param pinNum The pin number (0-7).
 * @param state The state to set (STATE_HIGH or STATE_LOW).
 */
void setPinBState(char pinNum, char state);

/**
 * @brief Set the state of all pins on PORT B.
 *
 * @param state The state to set (STATE_HIGH or STATE_LOW).
 */
void setAllPortBState(char state);

/**
 * @brief Read the current state of PORT B.
 *
 * @return The value of PINB register.
 */
char readPortB();

/**
 * @brief Read the state of a specific pin on PORT B.
 *
 * @param pinNum The pin number (0-7).
 * @return The state of the specified pin.
 */
char readPinB(char pinNum) ;

/* PORT D function declarations */

/**
 * @brief Set the direction of multiple pins on PORT D.
 *
 * @param mask The bitmask for the pins to be configured.
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setPortDDirection(char mask, char direction);

/**
 * @brief Set the direction of a single pin on PORT D.
 *
 * @param pinNum The pin number (0-7).
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setPinDDirection(char pinNum, char direction);

/**
 * @brief Set all pins on PORT D to a specific direction.
 *
 * @param direction The direction to set (DIRECTION_OUT or DIRECTION_IN).
 */
void setAllPortDDirection(char direction);

/**
 * @brief Set the state of a specific pin on PORT D.
 *
 * @param pinNum The pin number (0-7).
 * @param state The state to set (STATE_HIGH or STATE_LOW).
 */
void setPinDState(char pinNum, char state);

/**
 * @brief Set the state of all pins on PORT D.
 *
 * @param state The state to set (STATE_HIGH or STATE_LOW).
 */
void setAllPortDState(char state);

/**
 * @brief Read the current state of PORT D.
 *
 * @return The value of PIND register.
 */
char readPortD();

/**
 * @brief Read the state of a specific pin on PORT D.
 *
 * @param pinNum The pin number (0-7).
 * @return The state of the specified pin.
 */
char readPinD(char pinNum);

#endif	/* TINY2313_DIO_H */

