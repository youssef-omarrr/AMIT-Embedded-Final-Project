#include "myI2C.h"

/* Initialization */
void init_I2C(char Address, char Clock) {
    TWAR = Address; // Set slave address
    TWBR = 24; // Temporarily set to achieve 400KHz
}

/* I2C Control Functions */
void I2C_Send_Start() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); // Send Start condition
}

void I2C_wait() {
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT to clear
}

char I2C_Check_Status(char Status_Code) {
    return(TWSR & 0xF8) == Status_Code ? 1 : 0; // Check status code
}

void I2C_Send_SLA(char SLAVE_ADDRESS, char mode) {
    if (mode == I2C_WRITE) {
        TWDR = SLAVE_ADDRESS; // Set slave address with write bit
    } else {
        TWDR = (SLAVE_ADDRESS) | 0x01; // Set slave address with read bit
    }
    TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
}

void I2C_Send_Data(char data) {
    TWDR = data; // Load data to be transmitted
    TWCR = (1 << TWINT) | (1 << TWEN); // Trigger transmission
}

void I2C_Send_Stop() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Send Stop condition
}

void I2C_Prepare_ACK() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Prepare ACK
}

void I2C_Prepare_NACK() {
    TWCR = (1 << TWINT) | (1 << TWEN); // Prepare NACK
}

/* Master Operations */
char I2C_Master_Recieve(char Slave_Address) {
    I2C_Send_Start(); // Send Start condition
    I2C_wait(); // Wait for completion

    if (!I2C_Check_Status(I2C_STATUS_MT_START)) // Check if Start was successful
        return -1;

    I2C_Send_SLA(Slave_Address, I2C_READ); // Send slave address with read bit
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MR_SLA_ACK)) {
        if (I2C_Check_Status(I2C_STATUS_MR_SLA_NO_ACK)) {
            I2C_Send_Stop(); // Stop if NACK received
        }
        return -1;
    }

    I2C_Prepare_NACK(); // Prepare NACK to end transmission
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MR_DATA_NO_ACK))
        return -1;

    char data = TWDR; // Read received data
    I2C_Send_Stop(); // Send Stop condition
    return data; // Return data
}

void I2C_Master_Transmit_Buffer(char Slave_Address, char* Data, char DataSize) {
    I2C_Send_Start(); // Send Start condition
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MT_START))
        return;

    I2C_Send_SLA(Slave_Address, I2C_WRITE); // Send slave address with write bit
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MT_SLA_ACK)) {
        if (I2C_Check_Status(I2C_STATUS_MR_SLA_NO_ACK)) {
            I2C_Send_Stop(); // Stop if NACK received
        }
        return;
    }

    for (int i = 0; i < DataSize; i++) {
        I2C_Send_Data(*(Data + i)); // Transmit each byte
        I2C_wait();
        if (!I2C_Check_Status(I2C_STATUS_MT_DATA_ACK)) {
            if (I2C_Check_Status(I2C_STATUS_MT_DATA_NO_ACK)) {
                I2C_Send_Stop(); // Stop if NACK received
            }
            return;
        }
    }
    I2C_Send_Stop(); // Send Stop condition
}

void I2C_Master_Recieve_Buffer(char Slave_Address, char* Data, char DataSize) {
    I2C_Send_Start(); // Send Start condition
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MT_START))
        return;

    I2C_Send_SLA(Slave_Address, I2C_READ); // Send slave address with read bit
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MR_SLA_ACK)) {
        if (I2C_Check_Status(I2C_STATUS_MR_SLA_NO_ACK)) {
            I2C_Send_Stop(); // Stop if NACK received
        }
        return;
    }

    // Receive DataSize - 1 bytes with ACK
    for (int i = 0; i < DataSize - 1; i++) {
        I2C_Prepare_ACK(); // Prepare ACK for each byte
        I2C_wait();
        if (!I2C_Check_Status(I2C_STATUS_MR_DATA_ACK)) {
            I2C_Send_Stop(); // Stop on failure
            return;
        }
        Data[i] = TWDR; // Store data in buffer
    }

    I2C_Prepare_NACK(); // Prepare NACK for last byte
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_MR_DATA_NO_ACK)) {
        I2C_Send_Stop(); // Stop on failure
        return;
    }
    Data[DataSize - 1] = TWDR; // Store the last byte in buffer
    I2C_Send_Stop(); // Send Stop condition
}

/* Slave Operations */
void I2C_Slave_Transmit(char data) {
    I2C_Prepare_ACK(); // Prepare ACK
    I2C_wait();

    if (I2C_Check_Status(I2C_STATUS_ST_SLA_ACK)) {
        I2C_Send_Data(data); // Transmit data
        I2C_wait();
        if (!(I2C_Check_Status(I2C_STATUS_ST_DATA_ACK)) || !(I2C_Check_Status(I2C_STATUS_ST_LAST_DATA)))
            return;
    }
}

char I2C_Slave_Recieve() {
    I2C_Prepare_ACK(); // Prepare ACK
    I2C_wait();

    if (I2C_Check_Status(I2C_STATUS_SR_SLA_ACK) || I2C_Check_Status(I2C_STATUS_SR_GEN_ACK)) {
        I2C_Prepare_ACK(); // Prepare ACK for data
        I2C_wait();
        if (!I2C_Check_Status(I2C_STATUS_SR_DATA_ACK) || !I2C_Check_Status(I2C_STATUS_SR_GEN_DATA_ACK))
            return -1;
    }
    return TWDR; // Return received data
}

void I2C_Slave_Recieve_Buffer(char* Data, char DataSize) {
    I2C_Prepare_ACK(); // Prepare ACK
    I2C_wait();

    if (!I2C_Check_Status(I2C_STATUS_SR_SLA_ACK) || I2C_Check_Status(I2C_STATUS_SR_GEN_ACK)) {
        for (int i = 0; i < DataSize; i++) {
            I2C_Prepare_ACK(); // Prepare ACK for each byte
            I2C_wait();
            if (!I2C_Check_Status(I2C_STATUS_SR_DATA_ACK) || !I2C_Check_Status(I2C_STATUS_SR_GEN_DATA_ACK))
                return;
            *(Data + i) = TWDR; // Store received data in buffer
        }
    }
}

void I2C_Slave_Transmit_Buffer(char* Data, char DataSize) {
    // Prepare ACK to start transmission
    I2C_Prepare_ACK();
    I2C_wait();

    // Check if slave address was acknowledged
    if (!I2C_Check_Status(I2C_STATUS_ST_SLA_ACK)) {
        return; // Exit if no acknowledgment
    }

    // Transmit each byte in the buffer
    for (int i = 0; i < DataSize; i++) {
        I2C_Send_Data(*(Data + i)); // Send the current byte
        I2C_wait(); // Wait for transmission to complete

        // Check if data was acknowledged
        if (!I2C_Check_Status(I2C_STATUS_ST_DATA_ACK)) {
            // If NACK received, exit transmission
            if (I2C_Check_Status(I2C_STATUS_MT_DATA_NO_ACK)) {
                return;
            }
        }
    }
}


