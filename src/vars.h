#ifndef _VARS_H
#define _VARS_H

#include "ctypes.h"
#include "timer.h"


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


i2c_sensor_t sensor0 = {1,2,3,4,5,6, {{"address", &sensor0.address,0},{0,0}} };

vars_t vars[4] = { {"timer",   &timer, 0 },
				   {"sensor0", &sensor0, &sensor0.vars},
                   {0,0,0}};

static vars_t *var_ptr = &vars;

static vars_t * const var_ptr_home = &vars;


#endif