#include "mqueue.h"

void mqueue_init(mqueue_t *mq)
{
    cfifo_init((cfifo_t*)mq);
}

uint8_t mqueue_put (mqueue_t *mq, msg_t *msg)
{
    return cfifo_put ((cfifo_t*)mq, msg);
}

uint8_t mqueue_get (mqueue_t *mq, msg_t *msg)
{
    return cfifo_get ((cfifo_t*)mq, msg);
}

uint8_t mqueue_cnt (mqueue_t *mq)
{
    return cfifo_cnt ((cfifo_t*)mq);
}




