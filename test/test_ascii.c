#include "unity.h"
#include "ascii.h"
#include "cstr.h"

static cfifo_t cf;

void setUp(void)
{
  cfifo_init(& cf);


}

void tearDown(void)
{
}


void test_ascii_uint32_to_ascii_hex(void)
{
    unsigned long long data = 0;
    unsigned int i = 0;
    unsigned short int val = 0;

    data = ascii_uint32_to_ascii_hex(&cf, 0xb9a9a7a9);

    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x30, val); //0
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x78, val); //x
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x42, val); //b
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x39, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x41, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x39, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x41, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x37, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x41, val);
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x39, val);
    //printf("%016llX\n", data);
}


void test_ascii_dec_to_uint32(void)
{
    unsigned int dec = 0;

    // supports only 12 digits
    dec = ascii_dec_to_uint32("923789123");
    TEST_ASSERT_EQUAL_HEX32(923789123, dec);

    dec = ascii_dec_to_uint32("9230007891230");
    TEST_ASSERT_EQUAL_HEX32(0, dec);

}

// uint32_t ascii_dec_to_uint32(char *str)
// {
//   int i;
//   char s[16];
//   int len = cstrlen(str);
//   uint64_t r = 0; //change to 2 x 32 bit numbers
//   uint64_t d = 0;
//   uint32_t e10[12] = {1,
//                       10,
//                       100,
//                       1000,
//                       10000,
//                       100000,
//                       1000000,
//                       10000000,
//                       100000000,
//                       1000000000,
//                       10000000000,
//                       100000000000,}; // 100B, max len == 12
//   #ifdef TEST
//   #include <stdio.h>
//   printf("len=%d\n",len);
//   #endif

//   if(len > 12)
//     return 0;

//   memclear( (uint8_t*)s, 16);

//   for(i = 0; i < len; i++)
//     s[i] = *(str+i) - ASCII_OFFSET;

//   for(i = 0; i < len; i++)
//      r = r + ( ( (uint64_t) s[len - 1 - i] ) << ( 4 * i ) );

//   #ifdef TEST
//   #include <stdio.h>
//   printf("r=0x%016llX\n",r);
//   #endif

//    for(i = 0; i < len; i++)
//     d += ((((0xfLL<<(4*i))&r) >> (4*i)) * e10[i]);

//   #ifdef TEST
//   #include <stdio.h>
//   printf("d=%016lld\n",d);
//   #endif

//   return (uint32_t) d;
// }

void test_ascii_hex_to_uint32(void)
{
    uint32_t hex = 0;

    hex = ascii_hex_to_uint32("0");
    TEST_ASSERT_EQUAL_HEX32(0, hex);

    hex = ascii_hex_to_uint32("x0x1");
    TEST_ASSERT_EQUAL_HEX32(0, hex);

    hex = ascii_hex_to_uint32("0x1");
    TEST_ASSERT_EQUAL_HEX32(0x1, hex);

    hex = ascii_hex_to_uint32("0xaaqaa");
    TEST_ASSERT_EQUAL_HEX32(0, hex);

    hex = ascii_hex_to_uint32("123123");
    TEST_ASSERT_EQUAL_HEX32(0, hex);

    hex = ascii_hex_to_uint32("0x1abcd");
    TEST_ASSERT_EQUAL_HEX32(0x1abcd, hex);

    hex = ascii_hex_to_uint32("0xaBcD1234");
    TEST_ASSERT_EQUAL_HEX32(0xabcd1234, hex);

    hex = ascii_hex_to_uint32("0xFfFf1901");
    TEST_ASSERT_EQUAL_HEX32(0xFfFf1901, hex);




}
