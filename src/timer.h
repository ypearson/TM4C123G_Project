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
    uint32_t   (*now)(void);
} clock_t;

typedef enum {ONE_SHOT, REPEAT}  pmode_t;
typedef enum {DISABLED, ENABLED} action_state_t;

typedef struct _action_t
{
    pmode_t            mode;
    uint32_t           delay_time;
    uint32_t           start_time;
    uint8_t          (*start)(int argc, char **argv);
    action_state_t     state;
    struct _action_t  *linked_action;
} action_t;

typedef struct _stimer_t;
{
    clock_t clock;
    action_t actions[];
} stimer_t;

extern timer_t timer;
static timer_t *ptimer = &timer;

void     timer_init(void);
void     timer_tick(void);
uint32_t timer_get_time_now(void);
uint32_t timer_elasped(uint32_t t0, uint32_t t1);

#endif