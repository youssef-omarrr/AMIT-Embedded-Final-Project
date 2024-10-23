#include "TWI.h"
#include <xc.h>

#define SLAVE_ADDRESS_WRITE 0xA0 // Address of the slave device in write mode
#define SLAVE_ADDRESS_READ  0xA1 // Address of the slave device in read mode


void test_TWI(){
        // Initialize the I2C bus
    TWI_init();
    
    // Variable to store received data
    unsigned char received_data;

    while (1) {
        // Start I2C communication
        TWI_send_start();

        // Send slave address with the write bit
        if (TWI_write_byte(SLAVE_ADDRESS_WRITE) == 0) {
            // Successfully sent the slave address and received ACK
            // Now send some data to the slave
            TWI_write_byte(0xFF);  // Example data byte
        }
        
        // Stop I2C communication after sending data
        TWI_send_stop();
        
        _delay_ms(500);  // Delay between write and read operations

        // Start I2C communication again to read data from the slave
        TWI_send_start();
        
        // Send slave address with the read bit
        if (TWI_write_byte(SLAVE_ADDRESS_READ) == 0) {
            // Successfully sent the slave address and received ACK
            // Now read a byte from the slave
            received_data = TWI_read_byte(0);  // Send NACK after receiving 1 byte
        }

        // Stop I2C communication
        TWI_send_stop();
        
        _delay_ms(1000); // Delay for the next cycle
    }

}