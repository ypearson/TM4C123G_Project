#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ctypes.h"

#define SW1 PF4
#define SW2 PF0

typedef enum {NOT_PRESSED, PRESSED, DEBOUNCE} button_state_t;

typedef struct
{
	button_state_t state;
	uint32_t timestamp;
	uint32_t dtime;
	uint8_t self;
	uint8_t (*get)     (void);
	void    (*trigger) (void);
	void    (*enable)  (uint8_t);
	void    (*disable) (uint8_t);
} push_button_t;

typedef struct
{
	push_button_t   *sw[4];
	void (*handler) (uint8_t);
} push_buttons_t;

void button_init(void);
void button_action(uint8_t button);
void button_action_sw1(void);
void button_action_sw2(void);
void button_handler(uint8_t sw);
void button_handler1(push_buttons_t *btn);

uint8_t button_get_state(uint8_t sw);
uint8_t button_get_state_sw1(void);
uint8_t button_get_state_sw2(void);

void button_enable(uint8_t sw);
void button_disable(uint8_t sw);

static push_button_t sw1;
static push_button_t sw2;
push_buttons_t buttons;

#endif