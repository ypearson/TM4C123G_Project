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
#define i2c0_master_busy_wait() while(I2C0_MCS_R & I2C_MCS_BUSY)

typedef struct 
{
    #define I2C_BUF_SZ 32
    uint8_t buf[I2C_BUF_SZ];
    uint8_t sz;
} i2c_buffer_t;

typedef struct 
{
    uint8_t  num;
    uint8_t  address;
    void    (*init) (void);
    uint8_t (*read) (uint8_t addr, i2c_buffer_t *i2cb, uint8_t len);
    uint8_t (*write)(uint8_t addr, i2c_buffer_t *i2cb, uint8_t len);
    i2c_buffer_t i2cb;
    
} i2c_device_t;

void    i2c_device0_init(void);
void    i2c_device_init(i2c_device_t *dev, uint8_t num);

void    i2c0_master_init(void);
uint8_t i2c0_master_rx_byte_polling (uint8_t slave_address);
uint8_t i2c0_master_tx_byte_polling (uint8_t slave_address, uint8_t *byte);

uint8_t i2c0_master_rx_bytes_polling(uint8_t slave_address, i2c_buffer_t *i2cb, uint8_t len);
uint8_t i2c0_master_tx_bytes_polling(uint8_t slave_address, i2c_buffer_t *i2cb, uint8_t len);

uint8_t i2c0_master_tx_to_rx_bytes_polling(uint8_t slave_address, uint8_t len);
void    i2c0_enable_int(void);

// Slave

void    i2c0_slave_init(void);
uint8_t i2c0_slave_rxtx_byte_polling(uint8_t *byte, uint8_t blocking);



#define I2C_SLAVE_MODE 0
#endif
