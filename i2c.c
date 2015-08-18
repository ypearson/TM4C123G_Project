#include "tm4c123gh6pm.h"
#include "i2c.h"



void i2c0_master_init(void)
{
    volatile uint32_t delay;
    SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R0;
    delay = SYSCTL_RCGCI2C_R;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTB_AFSEL_R |= ( I2C0SCL|I2C0SDA );
    GPIO_PORTB_DEN_R   |= ( I2C0SCL|I2C0SDA );
    GPIO_PORTB_ODR_R   |= ( I2C0SDA );
    I2C0_MCR_R = I2C_MCR_MFE;
    I2C0_MTPR_R = ( SYS_FREQ_HZ ) / ( 20u * SCL_FREQ_HZ ) - 1u;
}

void i2c0_master_rxtx_byte_polling(uint8_t byte, uint8_t slave_address, uint8_t mode)
{
    uint32_t msa = ( slave_address << 1 ) | ( I2C_RXTX_MSK & mode );
    I2C0_MSA_R = msa;
    I2C0_MDR_R = byte;
    I2C0_MCS_R |= ( I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN);
    while( I2C0_MCS_R & I2C_MCS_BUSY );
}


void I2C0_Handler(void)
{

}