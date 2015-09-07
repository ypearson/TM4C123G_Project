#ifndef _CTYPES_H
#define _CTYPES_H

#ifdef TEST
#include "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdint.h"
#else
typedef unsigned char       uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;
#endif
#endif