#ifndef _CFIFO_H
#define _CFIFO_H

#include "ctypes.h"

typedef struct
{
	#define SZ 512u
	uint8_t  buf[SZ];
	uint8_t *head;
	uint8_t *tail;
	uint16_t  sz;
	uint16_t  cnt;
} cfifo_t;

void     cfifo_init(cfifo_t *cf);
uint8_t  cfifo_put (cfifo_t *cf, uint8_t *val);
uint8_t  cfifo_get (cfifo_t *cf, uint8_t *val);
uint8_t  cfifo_peek(cfifo_t *cf, uint8_t *val);
uint8_t  cfifo_pop (cfifo_t *cf, uint8_t *val);
uint16_t cfifo_cnt (cfifo_t *cf);

void    cfifo_to_cfifo_transfer(cfifo_t *scf, cfifo_t *dcf);
uint8_t cfifo_copy_string(const char *str, cfifo_t *cf);

#endif
