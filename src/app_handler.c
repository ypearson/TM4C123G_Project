#include "app_handler.h"
#include "mqueue.h"

 mqueue_t application_mq;

void app_handler_init(void)
{
    mqueue_init(&application_mq);
}

void app_handler_run(void)
{
    uint8_t ret = 0;
    msg_t msg = 0;

    if(!mqueue_cnt(&application_mq))
    {
        mqueue_get(&application_mq, msg)

        switch(msg)
        {
            case MSG_BUTTON_PRESS_SW1:
            break;

            case MSG_BUTTON_PRESS_SW2:
            break;

            default;
            break;

        }

    }

}