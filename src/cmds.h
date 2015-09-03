#ifndef _CMDS_H
#define _CMDS_H

#include "ctypes.h"

typedef struct
{
	const char *name;
	const char *usage;
	uint8_t (*fnc)(int argc, char **argv);
} cmd_t;


#endif
