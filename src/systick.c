#include "tm4c123gh6pm.h"
#include "systick.h"
#include "adc.h"
#include "i2c.h"
#include "gpio.h"
#include "hih6130.h"
#include "uart.h"
#include "button.h"
#include "led.h"

static uint8_t toggle = 0;

void systick_init(unsigned long period)
{
  timer_init();
  NVIC_ST_RELOAD_R = 0xFFFFF & period;
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

void timer_init(void)
{
  timer.cnt1  = 0;
  timer.cnt2  = 0;
  timer.pcnt  = & timer.cnt2;
}

uint32_t timer_elasped(uint32_t t0, uint32_t t1)
{
	uint32_t delta = 0;

	if( t1 >= t0 )
		delta = t1 - t0;
	else
		delta = t0 - t1;

	return delta;
}

void timer_tick(void)
{
	if( timer.pcnt == (&timer.cnt2) )
	{
		timer.cnt1 +=   timer.cnt2 + 1;
		timer.pcnt  = & timer.cnt1;
	}
	else
	{
		timer.cnt2 +=   timer.cnt1 + 1;
		timer.pcnt  = & timer.cnt2;
	}

}

uint32_t timer_get_time(void)
{
	return *(timer.pcnt);
}

void SysTick_Handler(void)
{
	timer_tick();

	button_handler1(&buttons);
}
