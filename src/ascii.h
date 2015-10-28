#ifndef _ASCII_H
#define _ASCII_H

#include "ctypes.h"
#include "cfifo.h"

void     ascii_append_newline(cfifo_t *cf);
void     ascii_append_backspace(cfifo_t *cf);
void     ascii_append_prompt(cfifo_t *cf);
void     ascii_append_hex(cfifo_t *cf);
void     uint32_to_ascii(cfifo_t *cf, const uint32_t input);
uint64_t uint32_to_ascii_hex(cfifo_t *cf, const uint32_t input);

static const char* BACKSPACE = "\x8\x20\x8";
static const char* NEWLINE   = "\r\n";
static const char* PROMPT    = ">";
static const char* HEX       = "  0x";

#endif
