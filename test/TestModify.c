//
// Created by guyis on 2019/4/2.
//

#include "unity.h"

#include "../data/DataManager.h"
#include "../util/StringUtil.h"
#include "../model/Modify.h"
#include "../core/Database.h"
#include "../data/TableOrder.h"

void test_func() {
    PurchaseRecord *pr = GetById(PurchaseRecord, PURCHASE_RECORD, 1);
    SellingRecord *sr = GetById(SellingRecord, SELLING_RECORD, 1);
    TEST_ASSERT(deletePurchaseRecord(1))
    TEST_ASSERT(deleteSellingRecord(1))
    TEST_ASSERT(deleteOrder(1))
    TEST_ASSERT(modifyOrderOfPurchaseRecord(1, 1, pr))
    TEST_ASSERT(modifyOrderOfSellingRecord(3, 1, sr))
}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);

    DataManager_finalize();

    return UNITY_END();
}