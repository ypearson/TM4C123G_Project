#include "app_handler.h"
#include "mqueue.h"
#include "ctypes.h"
#include "pll.h"
#include "systick.h"
#include "adc.h"
#include "uart.h"
#include "i2c.h"
#include "gpio.h"
#include "timer.h"
#include "led.h"
#include "timer.h"

void app_handler_init(application_t *app)
{

    gpio_porta_init();

    led_init();

    button_init();

    timer_init();

    uart_init();

    systick_init(10000);

    systick_enable_int();

    mqueue_init(&application_mq);

    app->mq      = &application_mq;
    app->bt      = &buttons;
    app->uart    = &uart0;

}

void app_handler_run(application_t *app)
{
    msg_t msg = 0;

    if(mqueue_cnt(app->mq))
    {
        mqueue_get(app->mq, &msg);

        switch(msg)
        {
            case MSG_BUTTON_PRESS_SW1:
            button_handler(app->bt);
            break;

            case MSG_BUTTON_PRESS_SW2:
            button_handler(app->bt);
            break;

            default:
            break;

        }

    }

}