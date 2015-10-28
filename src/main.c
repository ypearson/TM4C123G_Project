#include "ctypes.h"
#include "pll.h"
#include "app_handler.h"

void enableInterrupts(void);

int main(void)
{
    volatile application_t app;

    pll_init();

    app_handler_init(&app);

    enableInterrupts();

    for(;;)
    {
        uart_cli(app.uart);
    }

    return 0;
}
