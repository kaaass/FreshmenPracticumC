//
// Created by Kevin on 2019/4/16.
//

#include "unity.h"
#include <stdio.h>
#include "../model/Forecase.h"

void test_func() {
    printf("%lf\n", forecasePurchasePrice(1553411025, 7));
    printf("%lf\n", forecaseSellingPrice(1553411344, 2));

}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);

    DataManager_finalize();

    return UNITY_END();
}