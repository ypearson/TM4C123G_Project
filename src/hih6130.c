#include "hih6130.h"
#include "i2c.h"

static hih6130_sensor_t hih6130_sensor0;
static i2c_device_t i2c_device0;

#define HM_HIGH (0u)
#define HM_LOW  (1u)
#define TMP_HIGH     (2u)
#define TMP_LOW      (3u)

void hih6130_sensor_init0(void)
{
    hih6130_sensor_init(& hih6130_sensor0);
}

void hih6130_sensor_init(hih6130_sensor_t * sensor)
{
    i2c_device_init(& i2c_device0, 0);

    sensor->status  = 0;
    sensor->address = HIH6130_SLAVE_ADDRESS;
    sensor->temperature_data = 0;
    sensor->humidity_data = 0;
    sensor->fetch = 0;
    sensor->fd = & i2c_device0;

    sensor->fd->init();
}

void hih6130_sensor_update0(void)
{
    hih6130_sensor_update(& hih6130_sensor0 );
}

void hih6130_sensor_update(hih6130_sensor_t * sensor)
{
    if(!sensor->fetch)
    {
        sensor->fd->write(sensor->address, &sensor->fd->i2cb, 1);
        sensor->fetch = 1;
    }
    else
    {
        sensor->fd->read(sensor->address, &sensor->fd->i2cb, 4);
        sensor->status = (sensor->fd->i2cb.buf[HM_HIGH] >> 6);
        sensor->humidity_data = ( 0x3f & (sensor->fd->i2cb.buf[HM_HIGH]) << 8) | ( sensor->fd->i2cb.buf[HM_LOW]);
        sensor->temperature_data = ( (sensor->fd->i2cb.buf[TMP_HIGH] << 8)  | (sensor->fd->i2cb.buf[TMP_LOW]) ) >> 2;
        sensor->fetch = 0;
    }

}

