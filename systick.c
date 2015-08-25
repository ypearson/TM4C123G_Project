#include "tm4c123gh6pm.h"
#include "systick.h"
#include "adc.h"
#include "i2c.h"
#include "gpio.h"

static uint8_t toggle = 0;

void systick_init(unsigned long period)
{
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

void SysTick_Handler(void)
{
  uint8_t byte = 0xab;
  if(!toggle)
  {
	i2c0_master_tx_byte_polling(0x27, &byte);
	toggle = 1;
  }
  else
  {
  	i2c0_master_rx_bytes_polling(0x27, 4);
  	toggle = 0;
  }

}
