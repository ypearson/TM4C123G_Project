#include "cmds.h"
#include "ascii_helpers.h"
#include "vars.h"
#include "uart.h"
#include "cstr.h"

vars_t vars[3] = { {"v0", 26, &vars[0].data},
                   {"v1", 16, &vars[1].data},
                   {0,0,0}};

cmd_t cmds[6] = {
                  {"help", "this is the usage statement for help.", cmd_help },
                  {"ls", "this is the usage statement for hello.", cmd_ls },
                  {"cd", "this is the usage statement for hello.", cmd_help },
                  {"get", "print value of target variable.", cmd_get},
                  {"set", "set value of target variable.", cmd_help},
                  {0,0,0}};

static cfifo_t cmd_cf;

uint8_t cmd_help(int argc, char **argv)
{
    uint8_t i = 0;
    cfifo_init(&cmd_cf);

    while(cmds[i].name)
    {
        ascii_append_newline(&cmd_cf);
        cfifo_copy_string(cmds[i].name, &cmd_cf);
        ascii_append_spaces(&cmd_cf);
        cfifo_copy_string(cmds[i].usage, &cmd_cf);
        i++;
    }
    ascii_append_newline(&cmd_cf);
    return 0;
}

uint8_t cmd_get(int argc, char **argv)
{
    uint8_t i = 0;
    cfifo_init(&cmd_cf);
    uart_newline(&cmd_cf);

  if(argc != 2)
    return 1;
  else
  {
     while(vars[i].name)
     {
      if(!cstrcmp(argv[1], vars[i].name))
      {
        cfifo_copy_string(vars[i].name, &cmd_cf);
        ascii_append_spaces(&cmd_cf);
        uint32_to_ascii(&cmd_cf, vars[i].data);
        cfifo_copy_string(vars[i].data, &cmd_cf);
        break;
      }
      i++;
     }
   }
  return 0;
}

uint8_t cmd_ls(int argc, char **argv)
{
  uint8_t i = 0;
  cfifo_init(&cmd_cf);
  ascii_append_newline(&cmd_cf);

  while(vars[i].name)
  {
    cfifo_copy_string(vars[i].name, &cmd_cf);
    ascii_append_spaces(&cmd_cf);
    uint32_to_ascii(&cmd_cf, vars[i].data);
    cfifo_copy_string(vars[i].data, &cmd_cf);
    ascii_append_hex(&cmd_cf);
    //uint32_to_ascii_hex(&cmd_cf, (uint32_t) &vars[i] );
    //cfifo_copy_string(vars[i].name, &cmd_cf);
    //uart_put_string(&cmd_cf);
    ascii_append_newline(&cmd_cf);
    i++;
  }

  return 0;
}

void process_cmd(cfifo_t *cf)
{
  uint8_t i;
  char arg[64];
  uint8_t byte = 0;
  uint8_t ret = 0;
  uint8_t new_arg = 1;
  char *argv[4];
  int argc = 0;

  for(i = 0; i < 64; i++)
  {
    arg[i] = 0;
  }
  i = 0;

  while(!ret)
  {
    for(;;)
    {
      ret = cfifo_get(cf, &byte);
      if(byte == 0x20 || ret)
      {
        new_arg = 1;
        break;
      }
      else if(new_arg)
      {
        new_arg = 0;
        argv[argc++] = arg+i;
        arg[i++] = byte;
      }
      else
        arg[i++] = byte;
    }
    arg[i++] = 0;
  }
  i = 0;

  while(cmds[i].name)
  {
    if(!cstrcmp(argv[0], cmds[i].name))
    {
      ret = cmds[i].fnc(argc,argv);
      cfifo_to_cfifo_transfer(cf, &cmd_cf);
      break;
    }
    i++;
  }
}
