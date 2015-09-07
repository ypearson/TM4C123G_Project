#ifndef _CMDS_H
#define _CMDS_H

#include "ctypes.h"

typedef struct
{
	const char *name;
	const char *usage;
	uint8_t (*fnc)(int argc, char **argv);
} cmd_t;



uint8_t cmd_help(int argc, char **argv);
uint8_t cmd_get(int argc, char **argv);
uint8_t cmd_ls(int argc, char **argv);

void process_cmd(void);


#endif
