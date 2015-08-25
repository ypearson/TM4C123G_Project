#include "gpio.h"
#include "tm4c123gh6pm.h"


void gpio_porta_init(void)
{
	volatile uint32_t delay;
	//SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // This will cause a Hard Fault
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
	delay = SYSCTL_RCGC2_R;

	GPIO_PORTA_DIR_R   |=  PA2;
	GPIO_PORTA_AFSEL_R &= ~PA2;
	GPIO_PORTA_PCTL_R  &=  ~( GPIO_PCTL_PA2_M );
	GPIO_PORTA_AMSEL_R &= ~PA2;
	GPIO_PORTA_DEN_R   |=  PA2;

	GPIO_PORTA_DATA_R  &=  ~PA2;
}

void gpio_porta_toggle(uint8_t pin)
{
	switch(pin)
	{
		case PA2:
			GPIO_PORTA_DATA_R ^= PA2;
		break;

		default:
		break;
	}
}

void gpio_porta_set(uint8_t pin, uint8_t level)
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
