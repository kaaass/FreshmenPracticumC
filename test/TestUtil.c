//
// Created by guyis on 2019/3/20.
//
#include "unity.h"

#include "../util/StringUtil.h"
#include "../util/Time.h"
#include "../data/DataManager.h"
#include "../core/Config.h"

void test_time() {
    Time test = Time_parseTime(1553011000);
    stringbuf nowTime = Time_toLocalString(Time_getNow());
    printf("Now time: %s", CSTR(nowTime));
    $STR_BUF(nowTime);
    TEST_ASSERT_EQUAL_INT(3, test.month);
    TEST_ASSERT_EQUAL_INT(19, test.day);
    TEST_ASSERT_EQUAL_INT(23, test.hour);
    TEST_ASSERT_EQUAL_INT(56, test.minute);
    TEST_ASSERT_EQUAL_INT(40, test.second);
}

void test_config() {
    DataManager_init();
    // 测试
    Config_setString(LITERAL("test"), LITERAL("string"));
    TEST_ASSERT(EQUAL(LITERAL("string"), Config_optString(LITERAL("test"), $init$)));
    TEST_ASSERT(EQUAL(LITERAL("default"), Config_optString(LITERAL("null"), LITERAL("default"))));
    Config_setInteger(LITERAL("int"), 233);
    Config_setDouble(LITERAL("double"), 233.33);
    TEST_ASSERT_EQUAL_INT(233, Config_optInteger(LITERAL("int"), 0));
    TEST_ASSERT_EQUAL_FLOAT(233.33, Config_optDouble(LITERAL("double"), 0.0));
    TEST_ASSERT_EQUAL_INT(666, Config_optInteger(LITERAL("null"), 666));
    DataManager_finalize();
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_time);
    RUN_TEST(test_config);

    return UNITY_END();
}
