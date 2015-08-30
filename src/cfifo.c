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

uint8_t cfifo_put(cfifo_t * cf, uint8_t *val)
{
    uint8_t res = 0;
    const uint8_t  sz = cf->sz;
    const uint8_t *head = cf->head;
    const uint8_t *tail = cf->tail;
    const uint8_t *buf = cf->buf;
    const uint8_t  cnt = cf->cnt;

    if(cnt < sz)
    {
        if(!head)
        {
            cf->head = cf->buf;
        }

        *cf->head = *val;

        if(head + 1 < buf + sz)
        {
            if(head + 1 == tail)
            {
                cf->head = 0;
                printf("put: head = NULL, cnt = %d\n", cf->cnt+1);

            }
            else
            {
                cf->head++;
                printf("put: head = %x, cnt = %d\n", cf->head - cf->buf, cf->cnt+1);
            }
        }
        else if(tail == buf)
        {
            cf->head = 0;
            printf("put: head = NULL, cnt = %d\n", cf->cnt+1);
        }
        else
        {
            cf->head = cf->buf;
            printf("put: head = %x, cnt = %d\n", cf->head - cf->buf, cf->cnt+1);
        }

        if(!tail)
        {
            cf->tail = head;
            printf("put: tail = %x, cnt = %d\n", cf->tail - cf->buf, cf->cnt+1);
        }
        cf->cnt++;
    }
    else
    {
        cf->head = 0;
        res = 1;
        printf("*put: head = NULL, cnt = %d\n", cf->cnt);
    }

    return res;
}

uint8_t cfifo_get(cfifo_t *cf, uint8_t *val)
{
    uint8_t res = 1;
    const uint8_t  sz = cf->sz;
    const uint8_t *head = cf->head;
    const uint8_t *tail = cf->tail;
    const uint8_t *buf = cf->buf;
    const uint8_t  cnt = cf->cnt;

    if( cnt )
    {
        *val = *cf->tail;
        if(tail + 1 < buf + sz)
        {
            if(tail + 1 == head)
            {
                cf->tail = 0;
                printf("get: tail = NULL, cnt = %d\n", cf->cnt-1);
            }
            else
            {
                cf->tail++;
                printf("get: tail = %x, cnt = %d\n", cf->tail - cf->buf, cf->cnt-1);
            }
        }
        else if (head == buf)
        {
            cf->tail = 0;
            printf("get: tail = NULL, cnt = %d\n", cf->cnt-1);
        }
        else
        {
            cf->tail = buf;
            printf("get: tail = %x, cnt = %d\n", cf->tail - cf->buf, cf->cnt-1);
        }
        if(!head)
        {
            cf->head = tail;
            printf("get: head = %x, cnt = %d\n", cf->head - cf->buf, cf->cnt-1);
        }
        cf->cnt--;
        res = 0;
    }
    else
    {
        cf->tail = 0;
        res = 1;
        printf("*get: tail = NULL, cnt = %d\n", cf->cnt);
    }

    return res;
}

uint8_t cfifo_peek(cfifo_t *cf, uint8_t *val)
{
    uint8_t res = 0;

    if(cf->cnt)
    {
        *val = *cf->tail;
    }
    else
    {
        res = 1;
    }

    return res;
}

uint8_t cfifo_cnt(cfifo_t *cf)
{
    return cf->cnt;
}


