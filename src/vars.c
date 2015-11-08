#include "vars.h"
#include "timer.h"
#include "sensor.h"


// typedef struct
// {
//     char      *name;
//     uint32_t  *pdata;
//     uint32_t   type_mask;
//     void      *vars;
// } vars_t;

#define U32 (0xffffffff)
#define U16 (0x0000ffff)
#define U8  (0x000000ff)

timer_t timer = {0, {{"cnt1", &timer.cnt1, U32, 0},{0,0,0}} };

sensor_t sensor0 = {217,211,390,421,315,3116, {
                                  {"address", &sensor0.address, U8,      0},
                                  {"status",  &sensor0.status,  U8,      0},
                                  {"reg0",    &sensor0.reg0,    U16,     0},
                                  {"reg1",    &sensor0.reg1,    U16,     0},
                                  {"reg2",    &sensor0.reg2,    U16,     0},
                                  {"reg3",    &sensor0.reg3,    U16,     0},
                                  {0,         0,                0,       0} }};

vars_t vars[4] = { {"timer",   &timer,   U32, &timer.vars },
				   {"sensor0", &sensor0, U32, &sensor0.vars},
                   {0,0,0}};

vars_t *var_ptr = &vars;

vars_t * const var_ptr_home = &vars;
