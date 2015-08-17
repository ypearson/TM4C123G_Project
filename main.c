
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"

void enableInterrupts(void);

int main(void)
{
    pll_init();

    adc0_init();

    systick_init(1000000);
    systick_enable_int();

    uart0_init();
    uart0_enable_int();

    enableInterrupts();
    //disableInterrupts();

    while(1);

    return 0;
}


