#include "unity.h"
#include "cfifo.h"

cfifo_t cf;

void setUp(void)
{

}

void tearDown(void)
{
}


void test_cfifo_test_init(void)
{

	cfifo_init(&cf);
	uint8_t i;

	for(i = 0; i < SZ; i++)
	{
		TEST_ASSERT_EQUAL_HEX8(cf.buf[i], 0);
	}

}

void test_cfifo_test_put_get(void)
{
	uint8_t val = 1;
	cfifo_put(&cf, &val);
	TEST_ASSERT_EQUAL_HEX8(cf.buf[0], 1);
	val = 9;
	cfifo_get(&cf, &val);
	TEST_ASSERT_EQUAL_HEX8(1, val);

	val = 1;
	cfifo_put(&cf, &val);
	val++;
	cfifo_put(&cf, &val);

	TEST_ASSERT_EQUAL_HEX8(cf.buf[0], 1);
	TEST_ASSERT_EQUAL_HEX8(cf.buf[1], 2);




}

