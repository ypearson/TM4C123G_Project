#ifndef _TIMER_H
#define _TIMER_H

#include "ctypes.h"
#include "vars.h"

typedef struct
{
    uint32_t   cnt1;
    vars_t   vars[];
} timer_t;

typedef struct
{
    uint32_t   tick;
} clock_t;


typedef enum {ONE_SHOT, REPEAT} pmode_t;

typedef struct
{
    int     (*start[4])(int argc, char **argv);
    uint32_t  delay;
    //uint32_t  start;
    pmode_t   mode;
} action_group_t;

typedef struct
{
    clock_t clock;
    action_group_t actions[];

} stimer_t;

extern timer_t timer;
static timer_t *ptimer = &timer;

void     timer_init(void);
void     timer_tick(void);
uint32_t timer_get_time_now(void);
uint32_t timer_elasped(uint32_t t0, uint32_t t1);


#endif