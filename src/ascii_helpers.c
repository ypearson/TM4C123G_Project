#include "ascii_helpers.h"

void uint32_to_ascii(cfifo_t *cf, const uint32_t input)
{
  #define ASCII_OFFSET (0x30)
  #define NULL         (0x00)
  #define SP           (0x20)

  uint8_t i = 0, r = 0;
  uint32_t num = input;
  uint8_t data[32];

  while( num )
  {
    num = num / 10;
    i++;
  }
  num = input;
  data[i--] = NULL; //TODO, sz

  while( num )
  {
    r = num % 10;
    num = num / 10;
    data[i--] = r + ASCII_OFFSET;
  }

  if( data[0] == SP)
  {
    data[0] = ASCII_OFFSET;
    data[1] = NULL; //TODO, sz
  }

  i = 0;

  while(data[i])
  {
    cfifo_put(cf, &data[i++]); // if full?
  }
}

uint64_t uint32_to_ascii_hex(cfifo_t *cf, const uint32_t input)
{
  const uint64_t lessa = 0x30;
  const uint64_t morea = 0x37;
  const uint64_t mask = 0xF;
  const uint64_t nine = 0x9;
  uint64_t input64 = 0;
  uint64_t data[8];
  uint8_t i;
  uint8_t val;

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
    val = (uint8_t) ( 0xFF & (input64 >> (2*(7-i)*4)) );
    cfifo_put(cf, &val);  // if full?
  }

  return input64;
}
