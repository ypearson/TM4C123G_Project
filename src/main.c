#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"
#include "i2c.h"
#include "gpio.h"
#include "timer.h"
#include "led.h"
#include "timer.h"

void enableInterrupts(void);

int main(void)
{
    pll_init();

    app_handler_init();

    gpio_porta_init();

    led_init();

    button_init();

    timer_init();

    systick_init(5000);
    systick_enable_int();

    enableInterrupts();

    for(;;)
    {
        app_handler_run();
    }

    return 0;
}
