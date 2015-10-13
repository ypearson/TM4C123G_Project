#ifndef _LED_H_
#define _LED_H_

#include "ctypes.h"

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

typedef enum {OFF, ON} state_t;

typedef struct
{
	state_t state;
	void (*on)(void);
	void (*off)(void);
} led_t;

typedef struct
{
	led_t *green;
	led_t *yellow;
	led_t *orange;
	led_t *red;
	led_t *white;
	led_t *blue;
} leds_t;


uint8_t led_green_toggle(void);
uint8_t led_red_toggle(void);
uint8_t led_blue_toggle(void);

void    led_init(void);
void    led_green_on(void);
void    led_green_off(void);
void    led_red_on(void);
void    led_red_off(void);
void    led_blue_on(void);
void    led_blue_off(void);
uint8_t led_turn_on(uint8_t led);
uint8_t led_turn_off(uint8_t led);

static led_t green;
static led_t red;
static led_t blue;
static leds_t leds;


#endif