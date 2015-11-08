#ifndef _CMDS_H
#define _CMDS_H

#include "ctypes.h"
#include "cfifo.h"

typedef struct
{
	const char *name;
	const char *usage;
	uint8_t (*fnc)(int argc, char **argv);
} cmd_t;

uint8_t cmd_help(int argc, char **argv);
uint8_t cmd_get(int argc, char **argv);
uint8_t cmd_set(int argc, char **argv);
uint8_t cmd_ls(int argc, char **argv);
uint8_t cmd_cd(int argc, char **argv);

uint8_t cmd_process_user_input(cfifo_t *cf);

#endif
