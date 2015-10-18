#ifndef _GPIO_H_
#define _GPIO_H_

#include "ctypes.h"

#define Px0 (1<<0)
#define Px1 (1<<1)
#define Px2 (1<<2)
#define Px3 (1<<3)
#define Px4 (1<<4)
#define Px5 (1<<5)
#define Px6 (1<<6)
#define Px7 (1<<7)

#define PA0 Px0
#define PA1 Px1
#define PA2 Px2
#define PA3 Px3
#define PA4 Px4
#define PA5 Px5
#define PA6 Px6
#define PA7 Px7

#define PF0 Px0
#define PF1 Px1
#define PF2 Px2
#define PF3 Px3
#define PF4 Px4
#define PF5 Px5
#define PF6 Px6
#define PF7 Px7

#define SW1 PF4
#define SW2 PF0

void    gpio_porta_init(void);
void    gpio_porta_set(uint8_t pin, uint8_t level);
uint8_t gpio_porta_get(uint8_t pin);

void    gpio_portf_init(void);
void    gpio_portf_set(uint8_t pin, uint8_t level);
uint8_t gpio_portf_get(uint8_t pin);

void    gpio_portf_setup_int(void);
void    gpio_portf_clear_int(uint8_t gpio);
void    gpio_portf_enable_int(uint8_t gpio);
void    gpio_portf_disable_int(uint8_t gpio);

uint8_t gpio_get_pf4(void);
uint8_t gpio_get_pf0(void);

#endif