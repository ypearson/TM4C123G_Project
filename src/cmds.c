#include "cmds.h"
#include "ascii.h"
#include "vars.h"
#include "uart.h"
#include "cstr.h"

cmd_t cmds[6] = {
                  {"help", "this is the usage statement for help.", cmd_help },
                  {"ls", "this is the usage statement for hello.", cmd_ls },
                  {"cd", "this is the usage statement for hello.", cmd_help },
                  {"get", "print value of target variable.", cmd_get},
                  {"set", "set value of target variable.", cmd_set},
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
        cfifo_copy_string("    ", &cmd_cf);
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
    ascii_append_newline(&cmd_cf);

  if(argc != 2)
    return 1;
  else
  {
     while(vars[i].name)
     {
      if(!cstrcmp(argv[1], vars[i].name))
      {
        cfifo_copy_string(vars[i].name, &cmd_cf);
        cfifo_copy_string("    ", &cmd_cf);
        ascii_uint32_to_ascii_hex(&cmd_cf, *vars[i].pdata);
        break;
      }
      i++;
     }
   }
  return 0;
}

uint8_t cmd_set(int argc, char **argv)
{
    uint8_t i = 0;
    cfifo_init(&cmd_cf);
    ascii_append_newline(&cmd_cf);
    ascii_uint32_to_ascii(&cmd_cf, argc);
    ascii_append_newline(&cmd_cf);
    cfifo_copy_string(argv[2], &cmd_cf);


    if(argc != 2)
        return 1;
    else
    {
        while(vars[i].name)
        {
            if(!cstrcmp(argv[1], vars[i].name))
            {
                cfifo_copy_string("!set!   ", &cmd_cf);
                *vars[i].pdata = 0x1;
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
    cfifo_copy_string("    ", &cmd_cf);
    ascii_uint32_to_ascii_hex(&cmd_cf, *vars[i].pdata);
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
  argc--; //fix

  cfifo_init(cf);

  while(cmds[i].name)
  {
    if(!cstrcmp(argv[0], cmds[i].name))
    {
      ret = cmds[i].fnc(argc,argv);
      if(ret)
        cfifo_copy_string("error\r\n", &cmd_cf);
      cfifo_to_cfifo_transfer(&cmd_cf, cf);
      break;
    }
    i++;
  }
}
