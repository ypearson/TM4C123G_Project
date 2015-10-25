#ifndef _UART_H
#define _UART_H

#include "ctypes.h"
#include "ascii_helpers.h"
#include "cfifo.h"

typedef struct
{
	cfifo_t *cf;
	void (*init)(void);
	void (*print)(cfifo_t *cf);

} uart_t;

void uart_init(void);
void uart0_init(void);
void uart0_enable_int(void);

void uart0_put_byte(uint8_t data);
void uart0_put_string(cfifo_t *cf, const char *str);
void uart0_print(cfifo_t *cf);

void uart0_cli(void);

void uart0_newline(cfifo_t *cf);
void uart0_error(cfifo_t *cf);
void uart0_prompt(cfifo_t *cf);
void uart0_newline(cfifo_t *cf);
void uart0_backspace(cfifo_t *cf);
void uart0_prompt(cfifo_t *cf);
void uart0_error(cfifo_t *cf);
void uart0_hex(cfifo_t *cf);
void uart0_spaces(cfifo_t *cf);

#endif