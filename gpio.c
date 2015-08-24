#include "gpio.h"
#include "tm4c123gh6pm.h"

#define PA2 (1<<2)
#define PA3 (1<<3)
#define PA4 (1<<4)
#define PA5 (1<<5)
#define PA6 (1<<6)
#define PA7 (1<<7)

void gpio_a_init(void)
{
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; //port A
	delay = SYSCTL_RCGCGPIO_R0;

	GPIO_PORTA_DIR_R   |=  PA2;
	GPIO_PORTA_AFSEL_R &= ~PA2;
	GPIO_PORTA_PCTL_R  &=  ~( GPIO_PCTL_PA2_M );
	GPIO_PORTA_AMSEL_R &= ~PA2;
	GPIO_PORTA_DEN_R   |=  PA2;
}

void gpio_a_set(uint8_t pin, uint8_t level)
{
	switch(pin)
	{
		case PA2:
			if(level)
				GPIO_PORTA_DATA_R |=  PA2;
			else
				GPIO_PORTA_DATA_R &= ~PA2;
		break;

		default:
		break;
	}

}