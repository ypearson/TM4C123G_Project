#include "cfifo.h"

void cfifo_init(cfifo_t *cf)
{
    uint16_t i = 0;

    cf->sz = SZ;
    cf->head = cf->buf;
    cf->tail = 0;
    cf->cnt = 0;

    for(i = 0; i < SZ; i++)
    {
        cf->buf[i] = 0;
    }
}

uint8_t cfifo_put(cfifo_t * cf, uint8_t *val)
{
    uint8_t res = 0;
    const uint16_t   sz   = cf->sz;
    const uint16_t   cnt  = cf->cnt;
    uint8_t * const head = cf->head;
    uint8_t * const tail = cf->tail;
    uint8_t * const buf  = cf->buf;

    if(cnt < sz)
    {
        if(!head)
            cf->head = cf->buf;

        *cf->head = *val;

        if(head + 1 < buf + sz)
        {
            if(head + 1 == tail)
                cf->head = 0;
            else
                cf->head++;
        }
        else if(tail == buf)
            cf->head = 0;
        else
            cf->head = cf->buf;

        if(!tail)
            cf->tail = head;

        cf->cnt++;
    }
    else
    {
        cf->head = 0;
        res = 1;
    }

    return res;
}

uint8_t cfifo_get(cfifo_t *cf, uint8_t *val)
{
    uint8_t res = 1;
    const uint16_t   sz   = cf->sz;
    const uint16_t   cnt  = cf->cnt;
    uint8_t * const head = cf->head;
    uint8_t * const tail = cf->tail;
    uint8_t * const buf  = cf->buf;

    if(cnt)
    {
        *val = *cf->tail;
        if(tail + 1 < buf + sz)
        {
            if(tail + 1 == head)
                cf->tail = 0;
            else
                cf->tail++;
        }
        else if (head == buf)
            cf->tail = 0;
        else
            cf->tail = buf;
        if(!head)
            cf->head = tail;

        cf->cnt--;
        res = 0;
    }
    else
    {
        cf->tail = 0;
        res = 1;
    }

    return res;
}

uint8_t cfifo_peek(cfifo_t *cf, uint8_t *val)
{
    uint8_t res = 0;
    const uint16_t cnt = cf->cnt;

    if(cnt)
    {
        *val = *cf->tail;
    }
    else
    {
        res = 1;
    }

    return res;
}

uint8_t cfifo_pop(cfifo_t *cf, uint8_t *val)
{
    uint8_t res = 0;
    const uint16_t   sz   = cf->sz;
    const uint16_t   cnt  = cf->cnt;
    uint8_t * const head = cf->head;
    uint8_t * const tail = cf->tail;
    uint8_t * const buf  = cf->buf;

    if(cnt)
    {
        if(!head) // full
        {
            if(tail == buf)
                cf->head = buf + sz - 1;
            else
                cf->head = tail - 1;

            *val = *cf->head;
            *cf->head = 0;
            cf->cnt--;
        }
        else
        {
            if(cnt == 1)
            {
                cf->cnt = 0;
                cf->tail = 0;
                cf->head = tail;
            }
            else
            {
                if(head == buf)
                    cf->head = buf + sz - 1;
                else
                    cf->head--;

                cf->cnt--;
            }

            *val = *cf->head;
            *cf->head = 0;
        }

    }
    else
    {
        res = 1;
    }

    return res;
}


uint16_t cfifo_cnt(cfifo_t *cf)
{
    return cf->cnt;
}

void cfifo_to_cfifo_transfer(cfifo_t *scf, cfifo_t *dcf)
{
    uint8_t val;

    while(cfifo_cnt(scf))
    {
        cfifo_get(scf, &val);
        cfifo_put(dcf, &val);
    }
}

uint8_t cfifo_copy_string(const char *str, cfifo_t *cf)
{
    uint8_t i = 0;
    while(*(str+i))
    {
        cfifo_put(cf, (uint8_t*)(str+i++));
    }
    return i;
}
