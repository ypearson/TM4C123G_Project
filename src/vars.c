#include "vars.h"
#include "timer.h"
#include "sensor.h"

#undef  SVAR
#define SVAR timer
timer_t SVAR = {0, { VAR(cnt1, U32, 0)
                     VAR_END()}};
#undef  SVAR
#define SVAR sensor0
sensor_t SVAR = {217,211,390,421,315,3116,{
                 VAR(address,U8,  0)
                 VAR(status, U8,  0)
                 VAR(reg0,   U16, 0)
                 VAR(reg1,   U16, 0)
                 VAR(reg2,   U16, 0)
                 VAR(reg3,   U16, 0)
                 VAR_END()}};

#undef  SVAR
#define SVAR sensor1
sensor_t SVAR = {27,21,90,21,15,116,{
                 VAR(address,U8,  0)
                 VAR(status, U8,  0)
                 VAR(reg0,   U16, 0)
                 VAR(reg1,   U16, 0)
                 VAR(reg2,   U16, 0)
                 VAR(reg3,   U16, 0)
                 VAR_END()}};


VARS = { STRUCT(timer)
         STRUCT(sensor0)
         STRUCT(sensor1)
         STRUCT_END()};

vars_t *var_ptr = &vars;
vars_t * const var_ptr_home = &vars;
