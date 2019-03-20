//
// Created by guyis on 2019/3/20.
//
#include "unity.h"

#include "../util/Time.h"

void test_time() {
    Time test = Time_parseTime(1553011000);
    printf("Now time: %s", Time_toLocalString(Time_getNow()));
    TEST_ASSERT_EQUAL_INT(3, test.month);
    TEST_ASSERT_EQUAL_INT(19, test.day);
    TEST_ASSERT_EQUAL_INT(15, test.hour);
    TEST_ASSERT_EQUAL_INT(56, test.minute);
    TEST_ASSERT_EQUAL_INT(40, test.second);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_time);

    return UNITY_END();
}
