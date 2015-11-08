#include "cmds.h"
#include "ascii.h"
#include "vars.h"
#include "uart.h"
#include "cstr.h"

extern vars_t *var_ptr;
extern vars_t *var_ptr_home;

cmd_t cmds[6] = {
                  {"help", "this is the usage statement for help.", cmd_help },
                  {"ls", "this is the usage statement for hello.", cmd_ls },
                  {"cd", "this is the usage statement for hello.", cmd_cd },
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
        ascii_append_space(&cmd_cf, 8);
        cfifo_copy_string(cmds[i].usage, &cmd_cf);
        i++;
    }
    ascii_append_newline(&cmd_cf);
    return 0;
}

 uint8_t cmd_get(int argc, char **argv)
 {
//     uint8_t i = 0;

//     if(argc != 2)
//         return 1;
//     else
//     {
//         cfifo_init(&cmd_cf);
//         ascii_append_newline(&cmd_cf);
//         while(vars[i].name)
//         {
//             if(!cstrcmp(argv[1], vars[i].name))
//             {
//                 cfifo_copy_string(vars[i].name, &cmd_cf);
//                 cfifo_copy_string("    ", &cmd_cf);
//                 ascii_uint32_to_ascii_hex(&cmd_cf, *vars[i].pdata);
//                 break;
//             }
//             i++;
//         }
//     }
     return 0;
 }

 uint8_t cmd_set(int argc, char **argv)
 {
    uint32_t input = 0;
    uint32_t *p;
    vars_t *v = var_ptr;

    if(argc != 2)
        return 1;
    else
    {
        cfifo_init(&cmd_cf);
        ascii_append_newline(&cmd_cf);

        if(ascii_hex_prefix(argv[2]))
          input = ascii_dec_to_uint32(argv[2]);
        else
          input = ascii_hex_to_uint32(argv[2]);

        while(v->name)
        {
            if(!cstrcmp(argv[1], v->name))
            {
                p = v->pdata;

                if(v->type_mask == U32)
                {
                    *((uint32_t*)p) = (uint32_t)input;
                }
                else if(v->type_mask == U16)
                {
                   *((uint16_t*)p) = (uint16_t)input;
                }
                else
                {
                    *((uint8_t*)p) = (uint8_t)input;
                }
                break;
            }
            v++;;
        }
    }

     return 0;
 }

uint8_t cmd_ls(int argc, char **argv)
{
  uint8_t i = 0;
  vars_t *v = var_ptr;

  cfifo_init(&cmd_cf);
  ascii_append_newline(&cmd_cf);
  cfifo_copy_string("name        address     value\r\n", &cmd_cf);
  cfifo_copy_string("----------------------------------\r\n", &cmd_cf);
  while(v->name)
  {
    i = cfifo_copy_string(v->name, &cmd_cf);
    ascii_append_space(&cmd_cf, 12-i);
    ascii_uint32_to_ascii_hex(&cmd_cf, v->pdata);
    ascii_append_space(&cmd_cf, 12-10);
    if(!v->vars)
        ascii_uint32_to_ascii_hex(&cmd_cf, (v->type_mask)&*(v->pdata) ); // fix
    else
        cfifo_copy_string("<struct>", &cmd_cf);
    ascii_append_newline(&cmd_cf);
    v++;
  }
  return 0;
}

uint8_t cmd_cd(int argc, char **argv)
{
  uint8_t i = 0;
  vars_t *v = var_ptr;
  void *p;
  cfifo_init(&cmd_cf);
  ascii_append_newline(&cmd_cf);

  if(!argc)
  {
    var_ptr = var_ptr_home;
    return 0;
  }

    while(v->name)
    {
        if(!cstrcmp( argv[1], v->name))
        {
            p = v->vars;
            if(p)
            {
                var_ptr = (vars_t*)p;
                cfifo_copy_string(v->name, &cmd_cf);
            }
            break;
        }
        v++;
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
