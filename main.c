#include "tm4c123gh6pm.h"


unsigned int glob1;
unsigned int glob2 = 5;
unsigned int glob22 = 909;
int glob3 = 7;

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
  /*
  1. Program the value in the STRELOAD register.
  2. Clear the STCURRENT register by writing to it with any value.
  3. Configure the STCTRL register for the required operation. */
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
  unsigned int i = glob2;
  glob2++;
  glob2++;
  glob1 = 6;
  systick_init(1000000);
  systick_enable_int();
  enableInterrupts();

  //disableInterrupts();

  while(1);
}


