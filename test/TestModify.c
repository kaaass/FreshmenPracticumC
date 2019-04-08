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
    Order *order = GetById(Order, ORDER, 1);
    Order *order2 = GetById(Order, ORDER, 3);
    int opId[MAX_OP_ID] = {1, 2, 3, 4};
    int opCount = 4;
    TEST_ASSERT(deletePurchaseRecord(pr))
    TEST_ASSERT(deleteSellingRecord(sr))
    TEST_ASSERT(deleteOrder(order))
    TEST_ASSERT(modifyOrder(order2, opId, opCount, 233.33))
}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);

    DataManager_finalize();

    return UNITY_END();
}