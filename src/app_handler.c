#include "app_handler.h"

 mqueue_t application_mq;

void app_handler_init(void)
{
    mqueue_init(&application_mq);
}

void app_handler_run(void)
{
    if( !mqueue_cnt(&application_mq))
    {

    }

}