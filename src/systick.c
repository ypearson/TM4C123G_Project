#include "tm4c123gh6pm.h"
#include "systick.h"
#include "button.h"
#include "timer.h"
#include "app_handler.h"

void systick_init(unsigned long period)
{
  NVIC_ST_RELOAD_R = 0xFFFFFF & period;
  NVIC_ST_CURRENT_R = 0;
}

void systick_enable_int(void)
{
  NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_INTEN + NVIC_ST_CTRL_ENABLE);
}

void systick_disable_int(void)
{
  NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_INTEN + NVIC_ST_CTRL_ENABLE);
}

void SysTick_Handler(void)
{
    timer_tick();

    //app_handler_run(&app); //fix!

}
