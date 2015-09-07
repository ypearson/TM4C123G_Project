#include "unity.h"
#include "ascii_helpers.h"

static buffer_t buf;

void setUp(void)
{
  buffer_init(& buf, bSZ);


}

void tearDown(void)
{
}


void test_ascii(void)
{
	unsigned long long data = 0;
	unsigned int i = 0;

	data = uint32_to_ascii_hex(& buf, 0xb9a9a7a9);


    TEST_ASSERT_EQUAL_HEX8(0x42, buf.data[0]);
    TEST_ASSERT_EQUAL_HEX8(0x39, buf.data[1]);
    TEST_ASSERT_EQUAL_HEX8(0x41, buf.data[2]);
    TEST_ASSERT_EQUAL_HEX8(0x39, buf.data[3]);
    TEST_ASSERT_EQUAL_HEX8(0x41, buf.data[4]);
    TEST_ASSERT_EQUAL_HEX8(0x37, buf.data[5]);
    TEST_ASSERT_EQUAL_HEX8(0x41, buf.data[6]);
    TEST_ASSERT_EQUAL_HEX8(0x39, buf.data[7]);



	printf("%016llX\n", data);


}


//    TEST_ASSERT_EQUAL_HEX8(2, val);
