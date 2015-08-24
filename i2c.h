#ifndef _I2C_H
#define _I2C_H

#include "ctypes.h"

#define PB3 (1<<3)
#define PB2 (1<<2)

#define I2C0SDA PB3
#define I2C0SCL PB2

#define K (1000u)
#define M (1000000u)

#define SCL_FREQ_HZ (100u*K)
#define SYS_FREQ_HZ ( 80u*M)

#define I2C_RXTX_MSK (0x1u)
#define I2C_RX       (0x1u)
#define I2C_TX       (0x0u)

#define I2C_SLAVE_ADDRESS (0x3b)

// Master
void    i2c0_master_init(void);
uint8_t i2c0_master_rx_byte_polling (uint8_t slave_address);
uint8_t i2c0_master_tx_byte_polling (uint8_t *byte, uint8_t slave_address);
uint8_t i2c0_master_rx_bytes_polling(uint8_t slave_address, uint8_t len);
uint8_t i2c0_master_tx_bytes_polling(uint8_t slave_address, uint8_t len);

// Slave

void i2c0_slave_init(void);
uint8_t i2c0_slave_rxtx_byte_polling(uint8_t *byte, uint8_t blocking);


#endif
