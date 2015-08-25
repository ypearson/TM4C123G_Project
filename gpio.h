#ifndef _GPIO_H_
#define _GPIO_H_

#include "ctypes.h"

#define PA2 (1<<2)
#define PA3 (1<<3)
#define PA4 (1<<4)
#define PA5 (1<<5)
#define PA6 (1<<6)
#define PA7 (1<<7)

void gpio_porta_init(void);
void gpio_porta_toggle(uint8_t pin);
void gpio_porta_set(uint8_t pin, uint8_t level);

#endif