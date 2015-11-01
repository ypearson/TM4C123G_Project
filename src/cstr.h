#ifndef _CSTRING_H
#define _CSTRING_H

#include "ctypes.h"

int  cstrlen(const char *str);
int  cstrcmp(const char *s1, const char *s2);
void memclear(uint8_t *pd, uint8_t sz);

#endif