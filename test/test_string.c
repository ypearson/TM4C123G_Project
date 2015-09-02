#include "unity.h"
#include "string.h"


void setUp(void)
{

}

void tearDown(void)
{
}


void test_string(void)
{
    int result = 3;


    result = cstrcmp( "hello ", "hello ");
    TEST_ASSERT_EQUAL_HEX32(0, result);

    result = cstrcmp( "hello1", "hello2");
    TEST_ASSERT_EQUAL_HEX32(1, result);

    result = cstrcmp( "hello", "hello22");
    TEST_ASSERT_EQUAL_HEX32(1, result);

    result = cstrcmp( "hello21", "hello22");
    TEST_ASSERT_EQUAL_HEX32(1, result);

    result = cstrcmp( "$", "hello22");
    TEST_ASSERT_EQUAL_HEX32(1, result);

    result = cstrcmp( "", "hello22");
    TEST_ASSERT_EQUAL_HEX32(1, result);



}
