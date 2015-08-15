#include "tm4c123gh6pm.h"
#include "ctypes.h"
#include "pll.h"
#include "systick.h"

void enableInterrupts(void);

int main(void)
{
  pll_init();
  systick_init(1000000);
  systick_enable_int();
  enableInterrupts();
  //disableInterrupts();

  while(1);
}


