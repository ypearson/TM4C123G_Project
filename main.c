#include "tm4c123gh6pm.h"
#include "pll.h"

void enableInterrupts(void);

void SysTick_Handler(void)
{
    int i, j = 0;

    for(i=0; i < 3; i++)
    {
        j++;
    }
}

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

int main(void)
{
  pll_init();
  systick_init(1000000);
  systick_enable_int();
  enableInterrupts();
  //disableInterrupts();

  while(1);
}


