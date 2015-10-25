#ifndef _ASCII_H
#define _ASCII_H

#include "ctypes.h"
#include "cfifo.h"

void     uint32_to_ascii(cfifo_t *cf, const uint32_t input);
uint64_t uint32_to_ascii_hex(cfifo_t *cf, const uint32_t input);

#endif
