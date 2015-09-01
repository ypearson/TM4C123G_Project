#ifndef _CFIFO_H
#define _CFIFO_H

#include "ctypes.h"

typedef struct
{
	#define SZ 40
	uint8_t  buf[SZ];
	uint8_t *head;
	uint8_t *tail;
	uint8_t  sz;
	uint8_t  cnt;
} cfifo_t;

void    cfifo_init(cfifo_t *cf);
uint8_t cfifo_put (cfifo_t *cf, uint8_t *val);
uint8_t cfifo_get (cfifo_t *cf, uint8_t *val);
uint8_t cfifo_peek(cfifo_t *cf, uint8_t *val);
uint8_t cfifo_cnt (cfifo_t *cf);

#endif
