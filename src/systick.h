#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "ctypes.h"


typedef struct
{
	volatile uint32_t   cnt1;
	volatile uint32_t   cnt2;
	volatile uint32_t  *pcnt;

} timer_t;

void systick_init(unsigned long period);
void systick_enable_int(void);
void systick_disable_int(void);

void     timer_init(void);
void timer_tick(void);
uint32_t timer_get_time(void);
uint32_t timer_elasped(uint32_t t0, uint32_t t1);


timer_t timer;

#endif