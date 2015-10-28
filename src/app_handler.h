#ifndef _APP_HANDLER_H
#define _APP_HANDLER_H

#include "ctypes.h"
#include "mqueue.h"
#include "led.h"
#include "button.h"
#include "uart.h"

typedef struct
{
	mqueue_t       *mq;
	leds_t         *leds;
	push_buttons_t *bt;
	uart_t         *uart;

} volatile application_t;

void app_handler_init(application_t *app);
void app_handler_run(application_t *app);

#endif
