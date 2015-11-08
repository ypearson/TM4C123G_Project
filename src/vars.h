#ifndef _VARS_H
#define _VARS_H

#include "ctypes.h"

#define U32 (0xffffffff)
#define U16 (0x0000ffff)
#define U8  (0x000000ff)

typedef struct
{
    char      *name;
    uint32_t  *pdata;
    uint32_t   type_mask;
    void      *vars;
} vars_t;

#endif