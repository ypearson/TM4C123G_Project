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
