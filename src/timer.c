#include "timer.h"

void timer_init(void)
{
  ptimer->cnt1  = 0;
}

uint32_t timer_elasped(uint32_t t0, uint32_t t1)
{
	return (t1 >= t0) ? (t1 - t0) : (t0 - t1);
}

void timer_tick(void)
{
  ptimer->cnt1 = ptimer->cnt1 + 1;
}

uint32_t timer_get_time_now(void)
{
	return ptimer->cnt1;
}
