#include "hih6130.h"
#include "i2c.h"

static hih6130_sensor_t hih6130_sensor0;
static i2c_device_t i2c_device0;

void hih6130_sensor_init0(void)
{
    hih6130_sensor_init(& hih6130_sensor0);
}

void hih6130_sensor_init(hih6130_sensor_t * sen)
{
    i2c_device_init(& i2c_device0, 0);

    sen->status  = 0;
    sen->address = HIH6130_SLAVE_ADDRESS;
    sen->temperature_data = 0;
    sen->humidity_data = 0;
    sen->fetch = 0;
    sen->fd = & i2c_device0;

    sen->fd->init();
}

void hih6130_sensor_update(hih6130_sensor_t * sen)
{
    uint8_t byte = 0;

    if(!sen->fetch)
    {
        sen->fd->write(sen->address, & byte);
        sen->fetch = 1;
    }
    else
    {
        sen->fd->read(sen->address, sen->fd->i2cb/* this should be a address of */, 4)
        sen->fetch = 0;
    }

}

