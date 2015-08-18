#include "cfifo.h"


void cfifo_init(cfifo_t *cf)
{
	cf->sz = SZ;
	cf->head = cf->buf[0];
	cf->tail = cf->buf[SZ-1];
	cf->cnt = 0;
	for(i = 0; i < SZ; i++)
	{
		cf->buf[i] = 0;
	}
}

uint8_t cfifo_put(cfifo_t *cf, uint8_t *val)
{

}

uint8_t cfifo_get(cfifo_t *cf, uint8_t *val)
{
	if(cf->cnt == 0)
		return 0;


}

uint8_t cfifo_peek(cfifo_t *cf)
{

}

uint8_t cfifo_cnt(cfifo_t *cf)
{
	return cf->cnt;
}


