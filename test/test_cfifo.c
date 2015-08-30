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

void test_cfifo_test_simple_put_get(void)
{
    uint8_t val = 1;
    cfifo_put(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(cf.buf[0], 1);
    val = 9;
    cfifo_get(&cf, &val);
    TEST_ASSERT_EQUAL_HEX8(1, val);

    cfifo_init(&cf);

    val = 1;
    // if there is space return 0
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    // If full return 1
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));

    TEST_ASSERT_EQUAL_HEX8(1, cf.buf[0]);
    TEST_ASSERT_EQUAL_HEX8(2, cf.buf[1]);
    TEST_ASSERT_EQUAL_HEX8(3, cf.buf[2]);
    TEST_ASSERT_EQUAL_HEX8(4, cf.buf[3]);
    TEST_ASSERT_EQUAL_HEX8(4, cf.cnt);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(2, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(3, val);
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);

    // Return 1 is empty
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);

    cfifo_init(&cf);
}

void test_cfifo_test_wrap_put_get(void)
{
    cfifo_init(&cf);
    uint8_t val = 1;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(2, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(3, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);

    TEST_ASSERT_EQUAL_HEX8(1, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);

    TEST_ASSERT_EQUAL_HEX8(1, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);

    val = 1;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

}

void test_cfifo_test_wrap(void)
{
    cfifo_init(&cf);
    uint8_t val = 1;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

    val = 2;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(1, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(2, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(3, val);
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(4, val);
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(5, val);
    TEST_ASSERT_EQUAL_HEX8(1, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(5, val);
}

void test_cfifo_test_peek(void)
{

    cfifo_init(&cf);
    uint8_t val = 1;

    TEST_ASSERT_EQUAL_HEX8(1, cfifo_peek(&cf, &val));

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val = 10;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_peek(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

    val = 2;
    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));
    val++;

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_put(&cf, &val));

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_peek(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(1, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_peek(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(2, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(2, val);

    TEST_ASSERT_EQUAL_HEX8(0, cfifo_get(&cf, &val));
    TEST_ASSERT_EQUAL_HEX8(3, val);

    TEST_ASSERT_EQUAL_HEX8(1, cfifo_peek(&cf, &val));









}








