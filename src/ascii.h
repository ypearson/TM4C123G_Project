#ifndef _ASCII_H
#define _ASCII_H

#include "ctypes.h"
#include "cfifo.h"

#define ASCII_OFFSET (0x30)
#define SP           (0x20)

void     ascii_append_newline(cfifo_t *cf);
void     ascii_append_backspace(cfifo_t *cf);
void     ascii_append_prompt(cfifo_t *cf);
void     ascii_append_hex(cfifo_t *cf);
void     ascii_append_space(cfifo_t *cf, uint8_t num);

void     ascii_uint32_to_ascii(cfifo_t *cf, const uint32_t input);
uint64_t ascii_uint32_to_ascii_hex(cfifo_t *cf, const uint32_t input);

uint8_t ascii_hex_prefix(const char *str);
uint32_t ascii_dec_to_uint32(char *str);
uint32_t ascii_hex_to_uint32(const char *str);

const char* ascii_get_backspace(void);
const char* ascii_get_newline(void);
const char* ascii_get_prompt(void);

#endif
