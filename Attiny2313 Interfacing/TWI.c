#include "TWI.h"

void set_SCL_High() {
    setPinBState(PIN_SCL, STATE_HIGH);
}

void set_SDA_High() {
    setPinBState(PIN_SDA, STATE_HIGH);
}

void set_SCL_Low() {
    setPinBState(PIN_SCL, STATE_LOW);
}

void set_SDA_Low() {
    setPinBState(PIN_SDA, STATE_LOW);
}

void wait_SCL_High() {
    while (!(PORTB & (1 << PIN_SCL)));
}

void TWI_init() {
    // SDA and SCL must be set to output and HIGH before enabling the USI
    setPortBDirection((1 << PIN_SCL) | (1 << PIN_SDA), DIRECTION_OUT);
    set_SCL_High();
    set_SDA_High();

    USIDR = 0xFF;

    USICR = (1 << USIWM1) | (1 << USICS1) | (1 << USICLK); // Select Wire Mode (Two Wire)
                                                           // And The Clock Source

    USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
            (1 << USIDC) |    // Clear flags,
            (0x0 << USICNT0); // and reset counter.
}

void TWI_send_start() {
    // generate start condition
    set_SDA_High(); // SDA released
    set_SCL_High(); // SCL release until high
    wait_SCL_High();

    set_SDA_Low(); // SDA low (start condition)

    _delay_us(WAIT_LONG);

    set_SCL_Low(); // SCL low    

    set_SDA_High(); // SDA high (release to start transmitting)
}

void TWI_send_stop() {
    // SDA goes low
    set_SDA_Low();

    // release SCL
    set_SCL_High();
    wait_SCL_High();

    _delay_us(WAIT_LONG);

    // release SDA
    set_SDA_High();
    
    _delay_us(WAIT_SHORT);
}

unsigned char TWI_transfer(unsigned char usisr_mask) {

    // force SCL low (it's already low probably, since we're
    // toggling it up and down in pairs, but just in case...)
    set_SCL_Low();

    USISR = usisr_mask;

    // transfer until counter overflow
    do {
        _delay_us(WAIT_LONG);
        USICR |= (1 << USITC);
        wait_SCL_High(); // Waiting for SCL to go high
        _delay_us(WAIT_SHORT);
        USICR |= (1 << USITC);
    } while (!(USISR & (1 << USIOIF)));
    _delay_us(WAIT_LONG);

    // release SDA
    unsigned char temp = USIDR;
    USIDR = 0xFF; // 0x80 will work too (bit 7)

    return temp; // previous USIDR copy
}

// controller sends a byte to the bus
// returns 0 if there's a valid nack, otherwise 1
unsigned char TWI_write_byte(unsigned char data) {
    USIDR = data;
    TWI_transfer(USISR_CLOCK_8_BITS);

    // wait for ack
    setPortBDirection((1 << PIN_SDA), DIRECTION_IN); // set SDA to input
    unsigned char nack = TWI_transfer(USISR_CLOCK_1_BIT);
    setPortBDirection((1 << PIN_SDA), DIRECTION_OUT); // set SDA back to output

    return nack;
}

// controller reads 1 byte from the bus
// and sends a nack if wanna read another one
// (1 = will read another one, 0 = stop sending)
// returns the read byte
unsigned char TWI_read_byte(unsigned char nack) {
    setPortBDirection((1 << PIN_SDA), DIRECTION_IN); // receiving, so change to input
    unsigned char data = TWI_transfer(USISR_CLOCK_8_BITS);
    setPortBDirection((1 << PIN_SDA), DIRECTION_OUT); // set SDA back to output

    // send nack
    USIDR = nack;
    TWI_transfer(USISR_CLOCK_1_BIT);

    return data;
}
