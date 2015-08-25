#ifndef _HIH6130_H_
#define _HIH6130_H_

#include "ctypes.h"
#include "i2c.h"

typedef struct 
{
	#define HIH6130_SLAVE_ADDRESS 0x27
	uint8_t  status;
	uint16_t humidity_data;
	uint16_t temperature_data;
	uint8_t  address;
	uint8_t  fetch;
	i2c_device_t *fd;

} hih6130_sensor_t;

void hih6130_sensor_init0(void);
void hih6130_sensor_init(hih6130_sensor_t * sen);
void hih6130_sensor_update(hih6130_sensor_t * sen);

#endif
