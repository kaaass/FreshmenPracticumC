//
// Created by guyis on 2019/4/2.
//

#include "unity.h"

#include "../data/DataManager.h"
#include "../util/StringUtil.h"
#include "../model/Insert.h"

void test_has() {
    TEST_ASSERT(Insert_hasGuest(LITERAL("老王"), NULL));
    TEST_ASSERT(Insert_hasGuest(NULL, LITERAL("233-233-2233")));
    TEST_ASSERT(Insert_hasGuest(LITERAL("先辈"), LITERAL("114-514-1919")));
    TEST_ASSERT(!Insert_hasGuest(LITERAL("KAAAsS"), NULL));
    TEST_ASSERT(!Insert_hasGuest(NULL, LITERAL("000-000-0000")));
    TEST_ASSERT(!Insert_hasGuest(LITERAL("先辈"), LITERAL("000-000-0000")));
}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_has);

    DataManager_finalize();

    return UNITY_END();
}