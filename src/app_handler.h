#ifndef _APP_HANDLER_H
#define _APP_HANDLER_H

#include "ctypes.h"
#include "mqueue.h"
#include "led.h"
#include "button.h"

typedef struct
{
	mqueue_t       *mq;
	leds_t         *leds;
	push_buttons_t *bt;

} application_t;

void app_handler_init(void);
void app_handler_run(void);

static application_t app;

#endif
