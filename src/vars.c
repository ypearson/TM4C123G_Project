#include "vars.h"
#include "timer.h"
#include "sensor.h"


timer_t timer = {0, {{"cnt1", &timer.cnt1, 0},{0,0,0}} };

sensor_t sensor0 = {1,2,3,4,5,6, {{"address", &(sensor0.address),0},
                                  {"status",  &sensor0.status,   0},
                                  {"reg0",    &sensor0.reg0,     0},
                                  {0,         0,                 0} }};

vars_t vars[4] = { {"timer",   &timer, &timer.vars },
				   {"sensor0", &sensor0, &sensor0.vars},
                   {0,0,0}};

vars_t *var_ptr = &vars;

vars_t * const var_ptr_home = &vars;
