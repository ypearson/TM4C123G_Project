#include "unity.h"
#include "cstr.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_cstrlen(void)
{
    int len = 0;
    len = cstrlen("");
    TEST_ASSERT_EQUAL_HEX16(0, len);
    len = cstrlen("1");
    TEST_ASSERT_EQUAL_HEX16(1, len);
    len = cstrlen("12");
    TEST_ASSERT_EQUAL_HEX16(2, len);
    len = cstrlen("23456");
    TEST_ASSERT_EQUAL_HEX16(5, len);
    len = cstrlen("1234567890");
    TEST_ASSERT_EQUAL_HEX16(10, len);
}


void test_cstrcmp(void)
{
    int t = 0;
    t = cstrcmp("", "");
    TEST_ASSERT_EQUAL_HEX16(0, t);
    t = cstrcmp("abcdef", "abcdef");
    TEST_ASSERT_EQUAL_HEX16(0, t);
    t = cstrcmp("abcdef0", "abcdef1");
    TEST_ASSERT_EQUAL_HEX16(1, t);
    t = cstrcmp("abcdeF", "abcdef");
    TEST_ASSERT_EQUAL_HEX16(1, t);
}

void test_memclear(void)
{
    int i;
    char str[10] = "123456789";

    memclear( (unsigned char *) str, 10);

    for( i = 0; i < 10; i ++)
    {
        TEST_ASSERT_EQUAL_HEX8(0, str[i] );
    }
}
