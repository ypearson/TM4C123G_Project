#include "ascii.h"
#include "cstr.h"

static const char* BACKSPACE = "\x8\x20\x8";
static const char* NEWLINE   = "\r\n";
static const char* PROMPT    = "\r\n>";
static const char* HEX       = "0x";

void ascii_append_newline(cfifo_t *cf)
{
    cfifo_copy_string(NEWLINE, cf);
}

const char* ascii_get_newline(void)
{
  return NEWLINE;
}

void ascii_append_backspace(cfifo_t *cf)
{
    cfifo_copy_string(BACKSPACE, cf);
}

const char* ascii_get_backspace(void)
{
  return BACKSPACE;
}

void ascii_append_prompt(cfifo_t *cf)
{
    cfifo_copy_string(PROMPT, cf);
}

const char* ascii_get_prompt(void)
{
  return PROMPT;
}

void ascii_append_hex(cfifo_t *cf)
{
    cfifo_copy_string(HEX, cf);
}

void ascii_append_space(cfifo_t *cf, uint8_t num)
{
  uint8_t i;

  for(i = 0; i < num; i++)
    cfifo_copy_string(" ", cf);
}

void ascii_uint32_to_ascii(cfifo_t *cf, const uint32_t input)
{
  uint8_t i = 0, r = 0;
  uint32_t num = input;
  uint8_t data[32];

  while( num )
  {
    num = num / 10;
    i++;
  }
  num = input;
  data[i--] = 0; //null TODO, sz

  while( num )
  {
    r = num % 10;
    num = num / 10;
    data[i--] = r + ASCII_OFFSET;
  }

  if( data[0] == SP)
  {
    data[0] = ASCII_OFFSET;
    data[1] = 0; //null TODO, sz
  }

  i = 0;

  while(data[i])
  {
    cfifo_put(cf, &data[i++]); // if full?
  }
}

uint64_t ascii_uint32_to_ascii_hex(cfifo_t *cf, const uint32_t input)
{
  const uint64_t MASK  = 0xF;
  const uint64_t lessa = 0x30;
  const uint64_t morea = 0x37;
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
    data[i] = ( ( ( (uint64_t) input ) & ( MASK << 4*i ) ) << 4*i );
    if( ( (data[i] & ( MASK << 8*i) ) ) > ( nine << 8*i ) )
      data[i] += (morea << 8*i);
    else
      data[i] += (lessa << 8*i);
  }

  for(i = 0; i < 8; i++)
  {
    input64 += data[i];
  }

  ascii_append_hex(cf);

  for(i = 0; i < 8; i++)
  {
    val = (uint8_t) ( 0xFF & (input64 >> (2*(7-i)*4)) );
    cfifo_put(cf, &val);  // if full?
  }

  return input64;
}

uint32_t ascii_dec_to_uint32(char *str)
{
  #define MAX_BYTES 10
  #define loop() for(i = 0; i < len; i++)

  int i;
  char s[MAX_BYTES];
  int len = cstrlen(str);
  uint64_t r = 0; //change to 2 x 32 bit numbers
  uint64_t d = 0;
  const uint64_t MASK = 0xF;
  const uint32_t e10[MAX_BYTES] = {1,
                                   10,
                                   100,
                                   1000,
                                   10000,
                                   100000,
                                   1000000,
                                   10000000,
                                   100000000,
                                   1000000000,}; // 1B, max len == 10
  if(len > MAX_BYTES)
    return 0;

  memclear( (uint8_t*)s, MAX_BYTES);

  loop()
    s[i] = *(str+i) - ASCII_OFFSET;

  loop()
    r += ( ( (uint64_t) s[ (len-1) - i] ) << (4*i) );

  loop()
    d += ( (((MASK<<(4*i))&r) >> (4*i)) * e10[i] );

  #undef loop()
  #undef MAX_BYTES

  return (uint32_t) d;
}

uint8_t ascii_hex_prefix(const char *str)
{
  const char *hex = "0x";

  while(*hex) // check for 0x prefix
    if(*hex++ - *str++)
      return 1;

  return 0;
}

uint32_t ascii_hex_to_uint32(const char *str)
{
  #define MAX_BYTES (2+8+1) // prefix + 8 bytes + NULL
  #define loop() for(i = 0; i < len; i++)

  uint8_t  i = 0;
  uint32_t r = 0;
  int  len = cstrlen(str);
  char s[MAX_BYTES];
  char *p;
  const uint8_t lessa = 0x30;
  const uint8_t morea = 0x37;

  if( len < (2+1) || len > (2+8) )
    return 0;

  if(ascii_hex_prefix(str))
    return 0;

  len -= 2; // remove prefix length
  p = str + 2; // point to MSB, not prefix

  while(*p)
  {
    if(      !(*p < 0x30 || *p > 0x39) ) // 0-9
      p++;
    else if( !(*p < 0x61 || *p > 0x66) ) // a-f
      p++;
    else if( !(*p < 0x41 || *p > 0x46) )// A-F
      p++;
    else
      return 0;
  }

  memclear( (uint8_t*)s, MAX_BYTES);

  p = str + 2; // point to MSB, not prefix

  loop() // copy to non-const[]
    s[i] = *(p+i);
  p = s;

  while(*p)
  {
     if( ! (*p < 0x61 || *p > 0x66) ) // convert a-f --> A-F
        *p -= 0x20;
      p++;
  }
  p = s;

  while(*p)
  {
    if( *p > 0x40 ) // remove ascii offset
      *p -= morea;
    else
      *p -= lessa;
    p++;
  }

  loop()
    r += ( (uint32_t)s[i] << 4*(len-1 - i) ); //squeeze each byte together

  #undef MAX_BYTES
  #undef loop()

  return r;
}
