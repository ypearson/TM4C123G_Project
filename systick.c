#include "tm4c123gh6pm.h"
#include "systick.h"
#include "adc.h"
#include "i2c.h"

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
  i2c0_master_tx_bytes_polling(I2C_SLAVE_ADDRESS, 10);
  //i2c0_master_rx_byte_polling(I2C_SLAVE_ADDRESS);
  //i2c0_master_tx_byte_polling(&byte, I2C_SLAVE_ADDRESS);
}
