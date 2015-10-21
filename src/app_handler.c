#include "app_handler.h"
#include "mqueue.h"

void app_handler_init(void)
{
    mqueue_init(&application_mq);

    app.mq      = &application_mq;
    app.bt      = &buttons;

}

void app_handler_run(void)
{
    msg_t msg = 0;
    void *obj;

    if(mqueue_cnt(&application_mq))
    {
        mqueue_get(&application_mq, &msg);

        switch(msg)
        {
            case MSG_BUTTON_PRESS_SW1:
            obj = app.bt->sw[0];
            ((push_button_t*)obj)->state = PRESSED;
            button_handler(app.bt);
            break;

            case MSG_BUTTON_PRESS_SW2:
            obj = app.bt->sw[1];
            ((push_button_t*)obj)->state = PRESSED;
            button_handler(app.bt);
            break;

            default:
            break;

        }

    }

}