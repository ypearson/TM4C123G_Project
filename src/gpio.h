#ifndef _GPIO_H_
#define _GPIO_H_

#include "ctypes.h"

#define PA2 (1<<2)
#define PA3 (1<<3)
#define PA4 (1<<4)
#define PA5 (1<<5)
#define PA6 (1<<6)
#define PA7 (1<<7)

#define PF0 (1<<0)
#define PF1 (1<<1)
#define PF2 (1<<2)
#define PF3 (1<<3)
#define PF4 (1<<4)

#define SW1 PF4
#define SW2 PF0

#define RED_LED   PF1
#define BLUE_LED  PF2
#define GREEN_LED PF3

void    gpio_porta_init(void);
void    gpio_porta_set(uint8_t pin, uint8_t level);
uint8_t gpio_porta_get(uint8_t pin);

void gpio_portf_init(void);
void gpio_portf_set(uint8_t pin, uint8_t level);

#endif