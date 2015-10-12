#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ctypes.h"

#define PF0 (1<<0)
#define PF1 (1<<1)
#define PF2 (1<<2)
#define PF3 (1<<3)
#define PF4 (1<<4)

#define SW1 PF4
#define SW2 PF0

typedef enum {NOT_PRESSED, PRESSED, DEBOUNCE} button_state_t;

typedef struct
{
	button_state_t state;
	void (*trigger)(void);
} push_button_t;

typedef struct
{
	push_button_t *sw1;
	push_button_t *sw2;

} push_buttons_t;

void button_init(void);
void button_action(uint8_t button);
void button_action_sw1(void);
void button_action_sw2(void);

static push_button_t sw1;
static push_button_t sw2;
static push_buttons_t buttons;

#endif