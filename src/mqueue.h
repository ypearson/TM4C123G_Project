#ifndef _MQUEUE_H
#define _MQUEUE_H

#include "ctypes.h"
#include "cfifo.h"

#define MSG_BUTTON_PRESS_SW1 0x01
#define MSG_BUTTON_PRESS_SW2 0x02
#define MSG_02 0x03
#define MSG_03 0x04


typedef mqueue_t cfifo_t;
typedef msg_t    uint8_t;

void    mqueue_init(mqueue_t *mq);
uint8_t mqueue_put (mqueue_t *mq, msg_t *msg);
uint8_t mqueue_get (mqueue_t *mq, msg_t *msg);
uint8_t mqueue_cnt (mqueue_t *mq);

//mqueue_t application_mq;

#endif
