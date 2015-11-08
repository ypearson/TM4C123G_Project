#include "vars.h"
#include "timer.h"
#include "sensor.h"

timer_t timer = {0, { VAR(timer, cnt1, U32, 0)
                      VAR_END()}};

sensor_t sensor0 = {217,211,390,421,315,3116,{
                    VAR(sensor0, address,U8,  0)
                    VAR(sensor0, status, U8,  0)
                    VAR(sensor0, reg0,   U16, 0)
                    VAR(sensor0, reg1,   U16, 0)
                    VAR(sensor0, reg2,   U16, 0)
                    VAR(sensor0, reg3,   U16, 0)
                    VAR_END()}};

vars_t vars[] = { STRUCT(timer)
                  STRUCT(sensor0)
                  STRUCT_END()};

vars_t *var_ptr = &vars;
vars_t * const var_ptr_home = &vars;
