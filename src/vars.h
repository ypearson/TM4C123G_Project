#ifndef _VARS_H
#define _VARS_H

#include "ctypes.h"
#include "timer.h"

typedef struct
{
    char      *name;
    uint32_t  *pdata;
}vars_t;

vars_t vars[4] = { {"timer", &timer.cnt1 },
                   {0,0}};




#endif