#ifndef MY_I2C_H
#define	MY_I2C_H

#include <xc.h> 

//Start condition when SDA is falling when SCL is high
//Stop condition when SDA is rising  when SCL is high

#define I2C_MY_ADDRESS 0x69

#define I2C_PRESCALER_1 0
#define I2C_PRESCALER_4 1
#define I2C_PRESCALER_16 2
#define I2C_PRESCALER_64 3

#define I2C_WRITE 0
#define I2C_READ 1

// Master Transmitter (MT) mode
#define I2C_STATUS_MT_START         0x08  // Start condition transmitted
#define I2C_STATUS_MT_REP_START     0x10  // Repeated start condition transmitted
#define I2C_STATUS_MT_SLA_ACK       0x18  // SLA+W transmitted, ACK received
#define I2C_STATUS_MT_SLA_NO_ACK    0x20  // SLA+W transmitted, NACK received
#define I2C_STATUS_MT_DATA_ACK      0x28  // Data transmitted, ACK received
#define I2C_STATUS_MT_DATA_NO_ACK   0x30  // Data transmitted, NACK received
#define I2C_STATUS_MT_ARB_LOST      0x38  // Arbitration lost in SLA+W or data

// Master Receiver (MR) mode
#define I2C_STATUS_MR_ARB_LOST      0x38  // Arbitration lost in SLA+R or data
#define I2C_STATUS_MR_SLA_ACK       0x40  // SLA+R transmitted, ACK received
#define I2C_STATUS_MR_SLA_NO_ACK    0x48  // SLA+R transmitted, NACK received
#define I2C_STATUS_MR_DATA_ACK      0x50  // Data received, ACK returned
#define I2C_STATUS_MR_DATA_NO_ACK   0x58  // Data received, NACK returned

// Slave Transmitter (ST) mode
#define I2C_STATUS_ST_SLA_ACK       0xA8  // Own SLA+R received, ACK returned
#define I2C_STATUS_ST_ARB_LOST      0xB0  // Arbitration lost in SLA+RW
#define I2C_STATUS_ST_DATA_ACK      0xB8  // Data transmitted, ACK received
#define I2C_STATUS_ST_DATA_NO_ACK   0xC0  // Data transmitted, NACK received
#define I2C_STATUS_ST_LAST_DATA     0xC8  // Last data transmitted, ACK received

// Slave Receiver (SR) mode
#define I2C_STATUS_SR_SLA_ACK       0x60  // Own SLA+W received, ACK returned
#define I2C_STATUS_SR_ARB_LOST      0x68  // Arbitration lost in SLA+W
#define I2C_STATUS_SR_GEN_ACK       0x70  // General call received, ACK returned
#define I2C_STATUS_SR_GEN_ARB_LOST  0x78  // Arbitration lost in general call
#define I2C_STATUS_SR_DATA_ACK      0x80  // Data received, ACK returned
#define I2C_STATUS_SR_DATA_NO_ACK   0x88  // Data received, NACK returned
#define I2C_STATUS_SR_GEN_DATA_ACK  0x90  // General call data received, ACK returned
#define I2C_STATUS_SR_GEN_DATA_NO_ACK 0x98 // General call data received, NACK returned
#define I2C_STATUS_SR_STOP          0xA0  // Stop or repeated start condition received

// Miscellaneous states
#define I2C_STATUS_NO_INFO          0xF8  // No relevant state information
#define I2C_STATUS_BUS_ERROR        0x00  // Bus error due to illegal start/stop condition

// I2C Function Prototypes
void init_I2C(char Address, char Clock);
void I2C_Send_Start(void);
void I2C_wait(void);
char I2C_Check_Status(char Status_Code);
void I2C_Send_SLA(char SLAVE_ADDRESS, char mode);
void I2C_Send_Data(char data);
void I2C_Send_Stop(void);
void I2C_Prepare_ACK(void);

// Master Functions
void I2C_Master_Transmit(char Slave_Address, char data);
char I2C_Master_Recieve(char Slave_Address);
void I2C_Master_Transmit_Buffer(char Slave_Address, char* Data, char DataSize);
void I2C_Master_Recieve_Buffer(char Slave_Address, char* Data, char DataSize);

// Slave  Functions
void I2C_Slave_Transmit(char data);
char I2C_Slave_Recieve(void);
void I2C_Slave_Transmit_Buffer(char* Data, char DataSize);
void I2C_Slave_Recieve_Buffer(char*Data, char DataSize);

#endif	/* MY_I2C_H */

