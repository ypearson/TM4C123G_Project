#ifndef _SENSOR_H
#define _SENSOR_H

#include "ctypes.h"
#include "vars.h"


typedef struct
{
	uint8_t  address;
	uint8_t  status;
	uint16_t reg0;
	uint16_t reg1;
	uint16_t reg2;
	uint16_t reg3;
	vars_t   vars[];
} sensor_t;




#endif