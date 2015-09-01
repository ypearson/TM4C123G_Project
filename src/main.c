
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
    pll_init();

    gpio_porta_init();

    uart0_init();

    systick_init(200000);
    systick_enable_int();

    enableInterrupts();

    while(1);

    return 0;
}


