
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"
#include "i2c.h"
#include "gpio.h"
#include "hih6130.h"

void enableInterrupts(void);

int main(void)
{
    uint8_t byte = 0;

    pll_init();
    gpio_porta_init();

    if(!I2C_SLAVE_MODE)
    {
        systick_init(200000);
        systick_enable_int();
        hih6130_sensor_init0();
        enableInterrupts();
    }
    else
    {
        i2c0_slave_init();
        i2c0_slave_rxtx_byte_polling(&byte, 1);
    }

    while(1);

    return 0;
}


