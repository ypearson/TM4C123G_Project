#include "unity.h"
#include "ascii.h"
#include "cfifo.h"

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

    printf("%016llX\n", data);


}
