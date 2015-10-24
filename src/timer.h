#ifndef _TIMER_H
#define _TIMER_H

#include "ctypes.h"

typedef struct
{
	volatile uint32_t   cnt1;
	volatile uint32_t   cnt2;
	volatile uint32_t  *pcnt;

} timer_t;

void     timer_init(void);
void     timer_tick(void);
uint32_t timer_get_time(void);
uint32_t timer_elasped(uint32_t t0, uint32_t t1);

volatile timer_t timer;

#endif