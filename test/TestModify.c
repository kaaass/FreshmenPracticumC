//
// Created by guyis on 2019/4/2.
//

#include "unity.h"
#include <stdio.h>
#include "../data/DataManager.h"
#include "../util/StringUtil.h"
#include "../model/Modify.h"
#include "../core/Database.h"
#include "../data/TableOrder.h"

void test_func() {

    TEST_ASSERT(deletePurchaseRecord(1))
    TEST_ASSERT(GetById(PurchaseRecord, PURCHASE_RECORD, 1)->status == PURCHASE_DELETED)

    TEST_ASSERT(deleteSellingRecord(1))
    TEST_ASSERT(GetById(SellingRecord, SELLING_RECORD, 1)->status == SELLING_DELETED)

    TEST_ASSERT(deleteOrder(1))
    TEST_ASSERT(GetById(Order, ORDER, 1)->status == ORDER_DELETED)

    PurchaseRecord pr = {.price = 998244353};
    SellingRecord sr = {.price = 1e9 + 7};

    TEST_ASSERT(modifyOrderOfPurchaseRecord(1, 1, &pr))
    Order *order = GetById(Order, ORDER, Database_size(ORDER));
    TEST_ASSERT(GetById(PurchaseRecord, PURCHASE_RECORD, order->opId[order->opCount-1])->price == pr.price)

    TEST_ASSERT(modifyOrderOfSellingRecord(3, 1, &sr))
    order = GetById(Order, ORDER, Database_size(ORDER));
    TEST_ASSERT(GetById(SellingRecord, SELLING_RECORD, order->opId[order->opCount-1])->price == sr.price)

}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);

    DataManager_finalize();

    return UNITY_END();
}