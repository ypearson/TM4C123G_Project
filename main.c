
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"
#include "i2c.h"

#define SLAVE_MODE 1

void enableInterrupts(void);



int main(void)
{
    uint8_t ret;
    uint8_t byte = 0x66;

    pll_init();

    if(!SLAVE_MODE)
    {
        i2c0_master_init();
        systick_init(200000);
        systick_enable_int();
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


