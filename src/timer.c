#include "timer.h"

void timer_init(void)
{
  timer.cnt1  = 0;
  timer.cnt2  = 0;
  timer.pcnt  = & timer.cnt2;
}

uint32_t timer_elasped(uint32_t t0, uint32_t t1)
{
	uint32_t delta = 0;

	if( t1 >= t0 )
		delta = t1 - t0;
	else
		delta = t0 - t1;

	return delta;
}

void timer_tick(void)
{
	if( timer.pcnt == (&timer.cnt2) )
	{
		timer.cnt1 +=   timer.cnt2 + 1;
		timer.pcnt  = & timer.cnt1;
	}
	else
	{
		timer.cnt2 +=   timer.cnt1 + 1;
		timer.pcnt  = & timer.cnt2;
	}

}

uint32_t timer_get_time(void)
{
	return *(timer.pcnt);
}
