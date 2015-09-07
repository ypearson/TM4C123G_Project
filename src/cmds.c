#include "cmds.h"
#include "ascii_helpers.h"
#include "vars.h"
#include "uart.h"
#include "cstr.h"
#include "cfifo.h"


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


static cfifo_t uart0_cfifo;
static buffer_t buffer0;


uint8_t cmd_help(int argc, char **argv)
{
  uint8_t i = 0;

  while(cmds[i].name)
  {
    uart0_newline();
    uart0_put_string(cmds[i].name);
    uart0_spaces();
    uart0_put_string(cmds[i].usage);
    i++;
  }
  uart0_newline();
  return 0;
}

uint8_t cmd_get(int argc, char **argv)
{
  uint8_t i = 0;
  buffer_t buf;
  buffer_init(& buf, bSZ);
  uart0_newline();

  if(argc != 2)
    return 1;
  else
  {
     while(vars[i].name)
     {
      if(!cstrcmp(argv[1], vars[i].name))
      {
        uart0_put_string(vars[i].name);
        uart0_spaces();
        uint32_to_ascii(& buf, vars[i].data);
        uart0_put_string(buf.data);
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
  buffer_t buf;
  uart0_newline();

  while(vars[i].name)
   {
      uart0_put_string(vars[i].name);
      uart0_spaces();
      buffer_init(& buf, bSZ);
      uint32_to_ascii(& buf, vars[i].data);
      uart0_put_string(buf.data);
      buffer_init(& buf, bSZ);
      uart0_hex();
      uint32_to_ascii_hex(& buf, (uint32_t) &vars[i] );
      uart0_put_string(buf.data);
      uart0_newline();
      i++;
   }

  return 0;
}

void process_cmd(void)
{
  uint8_t i;
  char arg[64];
  char byte = 0;
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
      ret = cfifo_get(&uart0_cfifo, &byte);
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
      break;
    }
    i++;
  }
}
