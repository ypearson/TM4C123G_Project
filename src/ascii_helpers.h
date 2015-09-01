#ifndef _ASCII_HELPERS_H
#define _ASCII_HELPERS_H

#include "ctypes.h"

typedef struct
{
  #define bSZ (32u)
  char data[bSZ];
  uint8_t sz;
} buffer_t;

void buffer_init0(void);
void buffer_init(buffer_t *buf, uint8_t sz);
void buffer_print(buffer_t *buf, void (*print)(uint8_t byte), uint8_t stop );
void uint32_to_ascii(buffer_t * const buf, const uint32_t input);

#endif
