#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "button.h"
#include "led.h"
#include "systick.h"

void button_init(void)
{
    sw1.state   = NOT_PRESSED;
    sw1.trigger = button_action_sw1;
    sw1.get   = get_sw1;

    sw2.state = NOT_PRESSED;
    sw2.trigger = button_action_sw2;
    sw2.get   = get_sw2;

    buttons.sw1 = & sw1;
    buttons.sw2 = & sw2;

    buttons.sw1->trigger();
    buttons.sw2->trigger();

    buttons.sw1->trigger();
    buttons.sw2->trigger();

}

void button_action(uint8_t button)
{
    switch(button)
    {
        case SW1:
        button_action_sw1();
        break;

        case SW2:
        button_action_sw2();
        break;

        default:
        break;
    }
}

void debounce(uint8_t sw)
{
    uint8_t state = 0;

    switch(sw)
    {
        case SW1:
        if(sw1.state == PRESSED)
        {
            state = gpio_portf_get(SW1);
            if(state)
                sw1.trigger();

            sw1.state = NOT_PRESSED;
            gpio_portf_enable_int(SW1);

            systick_disable_int(); //bug here
        }
        break;

        case SW2:
        if(sw2.state == PRESSED)
        {
            state = gpio_portf_get(SW2);
            if(state)
                sw2.trigger();

            sw2.state = NOT_PRESSED;
            gpio_portf_enable_int(SW2);

            systick_disable_int(); //bug here
        }

        break;

        default:
        break;


    }
}

void button_action_sw1(void)
{
    uint8_t state = led_red_toggle();
    gpio_porta_set(PA6, state);

}

void button_action_sw2(void)
{
    uint8_t state = led_blue_toggle();
    gpio_porta_set(PA5, state);
}


void GPIOPortF_Handler(void)
{

    if(GPIO_PORTF_MIS_R & SW1)
    {
        gpio_portf_disable_int(SW1);
        GPIO_PORTF_ICR_R = SW1;
        sw1.state = PRESSED;
        systick_enable_int();


    }
    else if (GPIO_PORTF_MIS_R & SW2)
    {
        gpio_portf_disable_int(SW2);
        GPIO_PORTF_ICR_R = SW2;
        sw2.state = PRESSED;
        systick_enable_int();

    }

    //GPIO_PORTF_ICR_R


}