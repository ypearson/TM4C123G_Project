#include "gpio.h"
#include "tm4c123gh6pm.h"


void gpio_porta_init(void)
{
    volatile uint32_t delay;
    //SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // This will cause a Hard Fault
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTA_DIR_R   |=  ( PA5 | PA6 );
    GPIO_PORTA_AFSEL_R &= ~( PA5 | PA6 );
    GPIO_PORTA_PCTL_R  &= ~( PA5 | PA6 );
    GPIO_PORTA_AMSEL_R &= ~( PA5 | PA6 );
    GPIO_PORTA_DEN_R   |=  ( PA5 | PA6 );
}

void gpio_porta_set(uint8_t pin, uint8_t level)
{
    switch(pin)
    {
        case PA5:
            if(level)
                GPIO_PORTA_DATA_R |=  PA5;
            else
                GPIO_PORTA_DATA_R &= ~PA5;
        break;

        case PA6:
            if(level)
                GPIO_PORTA_DATA_R |=  PA6;
            else
                GPIO_PORTA_DATA_R &= ~PA6;
        break;

        default:
        break;
    }
}

uint8_t gpio_porta_get(uint8_t pin)
{
    uint8_t state = 0;

    switch(pin)
    {
        case PA5:
            state = ( GPIO_PORTA_DATA_R & PA5 );
        break;

        case PA6:
           state = ( GPIO_PORTA_DATA_R & PA6 );
        break;

        default:
        break;
    }

    return state;
}

void gpio_portf_init(void)
{
    volatile uint32_t delay;
    //SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // This will cause a Hard Fault
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    while(GPIO_PORTF_LOCK_R);
    GPIO_PORTF_CR_R  |= PF0;

    GPIO_PORTF_DIR_R   |=   ( PF1 | PF2 | PF3 );
    GPIO_PORTF_DIR_R   &=  ~( SW1 | SW2 );
    GPIO_PORTF_AFSEL_R &=  ~( PF1 | PF2 | PF3 | SW2 | SW1 );
    GPIO_PORTF_PCTL_R  &=  ~( PF1 | PF2 | PF3 | SW2 | SW1 );
    GPIO_PORTF_AMSEL_R &=  ~( PF1 | PF2 | PF3 | SW2 | SW1 );
    GPIO_PORTF_DEN_R   |=   ( PF1 | PF2 | PF3 | SW2 | SW1 );
}

void gpio_portf_set(uint8_t pin, uint8_t level)
{
    switch(pin)
    {
        case PF1:
            if(level)
                GPIO_PORTF_DATA_R |=  PF1;
            else
                GPIO_PORTF_DATA_R &= ~PF1;
        break;

        case PF2:
            if(level)
                GPIO_PORTF_DATA_R |=  PF2;
            else
                GPIO_PORTF_DATA_R &= ~PF2;
        break;

        case PF3:
            if(level)
                GPIO_PORTF_DATA_R |=  PF3;
            else
                GPIO_PORTF_DATA_R &= ~PF3;
        break;

        default:
        break;
    }
}
