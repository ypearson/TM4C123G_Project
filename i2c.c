#include "tm4c123gh6pm.h"
#include "i2c.h"
#include "gpio.h"

#define SZ 5
const uint8_t buffer[SZ] = {'h','e','l','l','o',};
uint8_t g_index = 0;

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

void i2c0_enable_int(void)
{
    NVIC_EN0_R  |= ( 1 << ( INT_I2C0 - 16) );
    NVIC_PRI2_R |= NVIC_PRI2_INT8_M; //lowest priority
    I2C0_MIMR_R  = I2C_MIMR_IM;
}

void i2c0_disable_int(void)
{
    I2C0_MIMR_R &= ~I2C_MIMR_IM;
}

uint8_t i2c0_master_tx_byte_polling(uint8_t slave_address, uint8_t *byte)
{
    uint8_t result = 0;
    i2c0_master_busy_wait();
    I2C0_MSA_R = ( slave_address << 1 ) | ( I2C_TX );
    I2C0_MDR_R = *byte;
    I2C0_MCS_R = ( I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN);
    i2c0_master_busy_wait();
    return result;
}

uint8_t i2c0_master_rx_byte_polling(uint8_t slave_address)
{
    uint8_t result;
    i2c0_master_busy_wait();
    I2C0_MSA_R = ( ( slave_address << 1 ) | ( I2C_RX ) );
    I2C0_MCS_R = ( I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN);
    i2c0_master_busy_wait();
    return (uint8_t)( I2C0_MDR_R & 0xFF  );
}

uint8_t i2c0_master_rx_bytes_polling(uint8_t slave_address, uint8_t len)
{
    uint8_t i = 0;
    uint8_t tmp;

    i2c0_master_busy_wait();
    I2C0_MSA_R = ( ( slave_address << 1 ) | ( I2C_RX ) );
    I2C0_MCS_R = ( I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_DATACK);
    i2c0_master_busy_wait();
    tmp = (uint8_t)( I2C0_MDR_R & 0xFF );

    for(i = 0; i < len - 2; i++)
    {
        I2C0_MCS_R = ( I2C_MCS_RUN | I2C_MCS_DATACK);
        i2c0_master_busy_wait();
        tmp = (uint8_t)( I2C0_MDR_R & 0xFF );
    }

    i2c0_master_busy_wait();
    I2C0_MCS_R = ( I2C_MCS_STOP | I2C_MCS_RUN );
    i2c0_master_busy_wait();
    tmp = (uint8_t)( I2C0_MDR_R & 0xFF );

    return tmp;
}

uint8_t i2c0_master_tx_bytes_polling(uint8_t slave_address, uint8_t len)
{
    uint8_t i = 0;
    uint8_t tmp = 0x96;

    i2c0_master_busy_wait();
    I2C0_MSA_R = ( ( slave_address << 1 ) | I2C_TX  );
    I2C0_MDR_R = tmp;
    I2C0_MCS_R = ( I2C_MCS_START | I2C_MCS_RUN );
    i2c0_master_busy_wait();

    for(i = 0; i < len - 2; i++)
    {
        I2C0_MDR_R = tmp;
        I2C0_MCS_R = ( I2C_MCS_RUN );
        i2c0_master_busy_wait();
    }

    I2C0_MDR_R = tmp;
    I2C0_MCS_R = ( I2C_MCS_STOP | I2C_MCS_RUN );
    i2c0_master_busy_wait();

    return tmp;
}

uint8_t i2c0_master_tx_to_rx_bytes_polling(uint8_t slave_address, uint8_t len)
{
    uint8_t i = 0;
    uint8_t tmp = 0x96;

    i2c0_master_busy_wait();
    I2C0_MSA_R = ( ( slave_address << 1 ) | I2C_TX  );
    I2C0_MDR_R = tmp;
    I2C0_MCS_R = ( I2C_MCS_START | I2C_MCS_RUN );
    
    i2c0_master_busy_wait();
    I2C0_MSA_R = ( ( slave_address << 1 ) | I2C_RX  );
    I2C0_MCS_R = ( I2C_MCS_RUN | I2C_MCS_START );
    while( I2C0_MCS_R & I2C_MCS_BUSY );

    for(i = 0; i < len - 2; i++)
    {
        I2C0_MDR_R = tmp;
        I2C0_MCS_R = ( I2C_MCS_RUN );
        i2c0_master_busy_wait();
    }

    I2C0_MDR_R = tmp;
    I2C0_MCS_R = ( I2C_MCS_STOP | I2C_MCS_RUN );
    i2c0_master_busy_wait();
    I2C0_MDR_R = tmp;

    return tmp;
}


void i2c0_slave_init(void)
{
    volatile uint32_t delay;
    SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R0;
    delay = SYSCTL_RCGCI2C_R;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTB_AFSEL_R |= ( I2C0SCL|I2C0SDA );
    GPIO_PORTB_DEN_R   |= ( I2C0SCL|I2C0SDA );
    GPIO_PORTB_ODR_R   |= ( I2C0SDA );
    I2C0_MCR_R  = I2C_MCR_SFE;
    I2C0_SCSR_R = I2C_SCSR_DA;
    I2C0_SOAR_R = I2C_SLAVE_ADDRESS;
}

uint8_t i2c0_slave_rxtx_byte_polling(uint8_t *byte, uint8_t blocking)
{
    uint8_t result = 0;

    do
    {
        if(I2C0_SCSR_R & I2C_SCSR_RREQ)
        {
            if(I2C0_SCSR_R & I2C_SCSR_FBR)
            {
                result = I2C0_SDR_R;
                *byte = 1;
            }
            else if(*byte == 1)
            {
                result = I2C0_SDR_R;   
            }
        }
        else if(I2C0_SCSR_R & I2C_SCSR_TREQ)
        {
            I2C0_SDR_R = 0x33;
        }
        else
        {
            //nothing to do.
        }
    } while(blocking);

    return result;
}


void I2C0_Handler(void)
{
    uint8_t tmp;
    I2C0_MICR_R = I2C_MICR_IC; // clear interrupt
    gpio_porta_toggle(PA2);


}