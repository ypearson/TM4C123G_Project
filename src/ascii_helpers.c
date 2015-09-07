#include "ascii_helpers.h"

void buffer_init(buffer_t *buf, uint8_t sz)
{
  uint8_t i;
  for(i = 0; i < sz; i++)
  {
    buf->data[i] = 0;
  }
  buf->sz = sz;
}

void buffer_print(buffer_t *buf, void (*print)(uint8_t byte), uint8_t stop )
{
  uint8_t i;
  for(i = 0; i < buf->sz; i++)
  {
    if(buf->data[i] == stop)
    {
      print(stop);
      break;
    }
    print(buf->data[i]);
  }
}

void uint32_to_ascii(buffer_t * const buf, const uint32_t input)
{
  #define ASCII_OFFSET (0x30)
  #define NULL         (0x00)
  #define SP           (0x20)

  uint8_t i = 0, r = 0;
  uint32_t num = input;

  while( num )
  {
    num = num / 10;
    i++;
  }
  num = input;
  buf->data[i--] = NULL; //TODO, sz

  while( num )
  {
    r = num % 10;
    num = num / 10;
    buf->data[i--] = r + ASCII_OFFSET;
  }

  if( buf->data[0] == SP)
  {
    buf->data[0] = ASCII_OFFSET;
    buf->data[1] = NULL; //TODO, sz
  }
}

uint64_t uint32_to_ascii_hex(buffer_t * const buf, const uint32_t input)
{
  uint64_t input64 = 0;
  uint64_t data[8];
  uint64_t lessa = 0x30;
  uint64_t morea = 0x37;
  uint64_t mask = 0xF;
  uint64_t nine = 0x9;
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    data[i] = 0;
  }

  for(i = 0; i < 8; i++)
  {
    data[i] = ( ( ( (uint64_t) input ) & ( mask << 4*i ) ) << 4*i );
    if( ( (data[i] & ( mask << 8*i) ) ) > ( nine << 8*i ) )
      data[i] += (morea << 8*i);
    else
      data[i] += (lessa << 8*i);
  }

  for(i = 0; i < 8; i++)
  {
    input64 += data[i];
  }

  for(i = 0; i < 8; i++)
  {
    buf->data[i] = (uint8_t) ( 0xFF & (input64 >> (2*(7-i)*4)) );
  }

  return input64;
}
