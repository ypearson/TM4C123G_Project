
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"
#include "i2c.h"

void enableInterrupts(void);

#define I2C_SLAVE_ADDRESS (0x3b)

int main(void)
{
    uint8_t ret;
    uint8_t byte = 0x66;

    pll_init();

    adc0_init();

    systick_init(1000000);
    systick_enable_int();

    uart0_init();
    uart0_enable_int();

    enableInterrupts();

    i2c0_master_init();

    ret = i2c0_master_rxtx_byte_polling(&byte, I2C_SLAVE_ADDRESS, I2C_TX);
    ret = i2c0_master_rxtx_byte_polling(&byte, I2C_SLAVE_ADDRESS, I2C_RX);

    while(1);

    return 0;
}


