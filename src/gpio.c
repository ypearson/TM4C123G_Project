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
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    while(GPIO_PORTF_LOCK_R);
    GPIO_PORTF_CR_R  |= PF0;

    GPIO_PORTF_DIR_R   |=   ( PF1 | PF2 | PF3 );
    GPIO_PORTF_DIR_R   &=  ~( PF4 | PF0 );
    GPIO_PORTF_AFSEL_R &=  ~( PF1 | PF2 | PF3 | PF4 | PF0 );
    GPIO_PORTF_PCTL_R  &=  ~( PF1 | PF2 | PF3 | PF4 | PF0 );
    GPIO_PORTF_AMSEL_R &=  ~( PF1 | PF2 | PF3 | PF4 | PF0 );
    GPIO_PORTF_DEN_R   |=   ( PF1 | PF2 | PF3 | PF4 | PF0 );

    GPIO_PORTF_PUR_R   |=  ( PF4 | PF0 );

    gpio_portf_setup_int();
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

uint8_t gpio_get_pf4(void)
{
    return gpio_portf_get(PF4);
}

uint8_t gpio_get_pf0(void)
{
    return gpio_portf_get(PF0);
}

uint8_t gpio_portf_get(uint8_t pin)
{
    uint8_t state = 1;

    switch(pin)
    {
        case PF4:
            state = ( GPIO_PORTF_DATA_R & PF4 );
        break;

        case PF0:
           state = ( GPIO_PORTF_DATA_R & PF0 );
        break;

        default:
        break;
    }

    return (!state) ? 1 : 0;
}

void gpio_portf_setup_int(void)
{
    // Edge trigger
    GPIO_PORTF_IS_R   &= ~( PF0 | PF4 );
    // One edge trigger
    GPIO_PORTF_IBE_R  &= ~( PF0 | PF4 );
    // Falling edge
    GPIO_PORTF_IEV_R  &= ~( PF0 | PF4 );
    // Enable interrupt
    GPIO_PORTF_IM_R  |=   ( PF0 | PF4 );

    NVIC_EN0_R  |= (1 << (INT_GPIOF-16));
    NVIC_PRI7_R |= NVIC_PRI7_INT30_M;
}

void gpio_portf_clear_int(uint8_t gpio)
{
    GPIO_PORTF_ICR_R = (gpio);
}

void gpio_portf_enable_int(uint8_t gpio)
{
    gpio_portf_clear_int(gpio);

    GPIO_PORTF_IM_R  |=   (gpio);
}

void gpio_portf_disable_int(uint8_t gpio)
{
    GPIO_PORTF_IM_R  &=  ~(gpio);
}

