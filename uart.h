#ifndef _UART_H
#define _UART_H

#include "ctypes.h"

void uart0_init(void);
void putbyte(uint8_t data);
void uart0_enable_int(void);


#endif