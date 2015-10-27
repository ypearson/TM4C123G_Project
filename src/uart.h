#ifndef _UART_H
#define _UART_H

#include "ctypes.h"
#include "ascii_helpers.h"
#include "cfifo.h"

typedef uint8_t device_t;

typedef struct
{
	device_t self;
	cfifo_t *cf;
	cfifo_t *ucf;
	void (*init)(void);
	void (*print)(device_t device, cfifo_t *cf);

} uart_t;

void uart_init(void);
void uart0_init(void);
void uart0_enable_int(void);

void uart_put_byte(device_t device, uint8_t data);
void uart_put_string(cfifo_t *cf, const char *str);
void uart_print(device_t device, cfifo_t *cf);

void uart_cli(uart_t *uart);

void uart_newline(cfifo_t *cf);
void uart_backspace(cfifo_t *cf);
void uart_prompt(cfifo_t *cf);
void uart_hex(cfifo_t *cf);

#endif