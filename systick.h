#ifndef _SYSTICK_H
#define _SYSTICK_H
void systick_init(unsigned long period);
void systick_enable_int(void);
void systick_disable_int(void);
#endif