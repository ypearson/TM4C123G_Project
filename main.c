
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"

void enableInterrupts(void);

int main(void)
{
  pll_init();
  adc0_init();
  systick_init(1000000);
  systick_enable_int();
  enableInterrupts();
  //disableInterrupts();

  while(1);
}


