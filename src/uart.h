#ifndef _UART_H
#define _UART_H

#include "ctypes.h"

#define PA1 (1<<1)
#define PA0 (1<<0)


void uart0_init(void);
void uart0_put_byte(uint8_t data);
void uart0_put_string(char *str);
void uart0_enable_int(void);
void uart0_newline(void);
void uart0_consume_incoming_data(void);
void uart0_start(void);
void uart0_prompt(void);



#endif