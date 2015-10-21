#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "button.h"
#include "led.h"
#include "timer.h"
#include "mqueue.h"

void button_init(void)
{
    sw1.self      = SW1;
    sw1.timestamp = 0;
    sw1.dtime     = 2000;
    sw1.state     = NOT_PRESSED;
    sw1.trigger   = button_action_sw1;
    sw1.get       = button_get_state_sw1;
    sw1.enable    = button_enable;
    sw1.disable   = button_disable;

    sw2.self      = SW2;
    sw2.timestamp = 0;
    sw2.dtime     = 2000;
    sw2.state     = NOT_PRESSED;
    sw2.trigger   = button_action_sw2;
    sw2.get       = button_get_state_sw2;
    sw2.enable    = button_enable;
    sw2.disable   = button_disable;

    buttons.sw[0]   = & sw1;
    buttons.sw[1]   = & sw2;
    buttons.sw[2]   = 0;
    buttons.sw[3]   = 0;

    //buttons.handler = button_handler;
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

void button_handler(push_buttons_t *b)
{
    uint8_t i = 1;
    uint8_t state = 0;
    uint32_t dt = 0;
    push_button_t *pb = *(b->sw);

    while(pb)
    {
        if(pb->state == PRESSED)
        {
            pb->timestamp = timer_get_time();
            pb->state = DEBOUNCE;
        }
        else if(pb->state == DEBOUNCE)
        {
             dt = timer_elasped(pb->timestamp, timer_get_time());
             if( dt >= pb->dtime )
             {
                state = pb->get();
                if(state)
                    pb->trigger();

                pb->timestamp = 0;
                pb->state = NOT_PRESSED;
                pb->enable(pb->self);
             }
        }
        pb = b->sw[i++];
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

uint8_t button_get_state(uint8_t sw)
{
    uint8_t state = 0;

    switch(sw)
    {
        case SW1:
        state = button_get_state_sw1();
        break;

        case SW2:
        state = button_get_state_sw2();
        break;

        default:
        break;
    }

    return state;
}

uint8_t button_get_state_sw1(void)
{
    return gpio_get_pf4();
}

uint8_t button_get_state_sw2(void)
{
    return gpio_get_pf0();
}

void button_enable(uint8_t sw)
{
    switch(sw)
    {
        case SW1:
        gpio_portf_enable_int(SW1);

        break;

        case SW2:
        gpio_portf_enable_int(SW2);
        break;

        default:
        break;
    }
}

void button_disable(uint8_t sw)
{
    switch(sw)
    {
        case SW1:
        gpio_portf_disable_int(SW1);
        break;

        case SW2:
        gpio_portf_disable_int(SW2);
        break;

        default:
        break;
    }
}

void GPIOPortF_Handler(void)
{
    msg_t msg;

    if(GPIO_PORTF_MIS_R & SW1)
    {
        gpio_portf_disable_int(SW1);
        gpio_portf_clear_int(SW1);
        msg = MSG_BUTTON_PRESS_SW1;
        mqueue_put(&application_mq, &msg);
    }
    else if(GPIO_PORTF_MIS_R & SW2)
    {
        gpio_portf_disable_int(SW2);
        gpio_portf_clear_int(SW2);
        msg = MSG_BUTTON_PRESS_SW2;
        mqueue_put(&application_mq, &msg);
    }
    else
    {

    }
}