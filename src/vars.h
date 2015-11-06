#ifndef _VARS_H
#define _VARS_H

#include "ctypes.h"


// typedef struct
// {
// 	volatile uint32_t   cnt1;

// } timer_t;

typedef struct
{
    char      *name;
    uint32_t  *pdata;
    void      *vars;
} vars_t;



typedef struct
{
	uint8_t  address;
	uint8_t  status;
	uint16_t reg0;
	uint16_t reg1;
	uint16_t reg2;
	uint16_t reg3;
	vars_t   vars[];
} i2c_sensor_t;




#endif