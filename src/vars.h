#ifndef _VARS_H
#define _VARS_H

#include "ctypes.h"

#define U32 (0xffffffffUL)
#define U16 (0x0000ffffUL)
#define U8  (0x000000ffUL)

#define VAR(structure,name,type,link) {#name, &structure.name, type, link},
#define VAR_END() {0,0,0,0}

#define STRUCT(name) {#name, &name, U32, &name.vars},
#define STRUCT_END() {0,0,0,0}

typedef struct
{
    char      *name;
    uint32_t  *pdata;
    uint32_t   type_mask;
    void      *vars;
} vars_t;

#endif