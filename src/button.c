#include "gpio.h"
#include "button.h"
#include "led.h"

void button_init(void)
{
    sw1.state = NOT_PRESSED;
    sw1.trigger = button_action_sw1;

    sw1.state = NOT_PRESSED;
    sw1.trigger = button_action_sw2;

    buttons.sw1 = & sw1;
    buttons.sw2 = & sw2;

    // buttons.sw1->trigger();
    // buttons.sw2->trigger();

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

void button_action_sw1(void)
{


}

void button_action_sw2(void)
{

}


void GPIOPortF_Handler(void)
{


}