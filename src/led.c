#include "gpio.h"
#include "led.h"


void led_init(void)
{
    gpio_portf_init();

    green.state = OFF;
    green.on = led_green_on;
    green.off = led_green_off;

    red.state = OFF;
    red.on = led_red_on;
    red.off = led_red_off;

    blue.state = OFF;
    blue.on = led_blue_on;
    blue.off = led_blue_off;

    leds.green = &green;
    leds.red   = &red;
    leds.blue  = &blue;

    leds.green->on();
    leds.green->off();

    leds.red->on();
    leds.red->off();

    leds.blue->on();
    leds.blue->off();
}

uint8_t led_green_toggle(void)
{
    if(leds.green->state)
        leds.green->off();
    else
        leds.green->on();

    return leds.green->state;
}

uint8_t led_red_toggle(void)
{
    if(leds.red->state)
        leds.red->off();
    else
        leds.red->on();

    return leds.red->state;
}

uint8_t led_blue_toggle(void)
{
    if(leds.blue->state)
        leds.blue->off();
    else
        leds.blue->on();

    return leds.blue->state;
}

void led_green_on(void)
{
    green.state = led_turn_on(GREEN_LED);
}

void led_green_off(void)
{
    green.state = led_turn_off(GREEN_LED);
}

void led_red_on(void)
{
    red.state = led_turn_on(RED_LED);
}

void led_red_off(void)
{
    red.state = led_turn_off(RED_LED);
}

void led_blue_on(void)
{
    blue.state = led_turn_on(BLUE_LED);
}

void led_blue_off(void)
{
    blue.state = led_turn_off(BLUE_LED);
}

uint8_t led_turn_on(uint8_t led)
{
    gpio_portf_set(led, ON);
    return ON;
}

uint8_t led_turn_off(uint8_t led)
{
    gpio_portf_set(led, OFF);
    return OFF;
}