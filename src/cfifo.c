#include "cfifo.h"

// typedef struct
// {
//  #define SZ 4
//  uint8_t  buf[SZ];
//  uint8_t *head;
//  uint8_t *tail;
//  uint8_t  sz;
//  uint8_t  cnt;
// } cfifo_t;

void cfifo_init(cfifo_t *cf)
{
    uint8_t i = 0;

    cf->sz = SZ;
    cf->head = cf->buf;
    cf->tail = 0;
    cf->cnt = 0;

    for(i = 0; i < SZ; i++)
    {
        cf->buf[i] = 0;
    }
}

uint8_t cfifo_put(cfifo_t *cf, uint8_t *val)
{
    *cf->head = *val;
    cf->head++;



}

uint8_t cfifo_get(cfifo_t *cf, uint8_t *val)
{
    *val = cf->buf[0];
}

uint8_t cfifo_peek(cfifo_t *cf)
{

}

uint8_t cfifo_cnt(cfifo_t *cf)
{
    return cf->cnt;
}


