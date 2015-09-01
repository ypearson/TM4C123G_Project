#ifndef _UART_H
#define _UART_H

#include "ctypes.h"

#define PA1 (1<<1)
#define PA0 (1<<0)


void uart0_init(void);
void putbyte(uint8_t data);
void uart0_enable_int(void);
void uart0_newline(void);
void uart0_consume_incoming_data(void);


#endif