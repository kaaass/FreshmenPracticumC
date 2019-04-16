//
// Created by Kevin on 2019/4/16.
//
#include "unity.h"
#include "../model/Gift.h"
#include <stdio.h>


void test_func() {
    //test getGift
    int sellingRecordset1[] = {5};
    int sellingRecordset2[] = {7};
    int sellingRecordset3[] = {3};
    int sellingRecordset4[] = {55};

    int mountingsId = getGift(sellingRecordset1, 1);
    TEST_ASSERT_EQUAL(mountingsId, -3);

    mountingsId = getGift(sellingRecordset2, 1);
    TEST_ASSERT_EQUAL(mountingsId, 2);

    mountingsId = getGift(sellingRecordset3, 1);
    TEST_ASSERT_EQUAL(mountingsId, 1);

    mountingsId = getGift(sellingRecordset4, 1);
    TEST_ASSERT_EQUAL(mountingsId, -1);

    //test insertGift
    TEST_ASSERT(insertGift(sellingRecordset1, 1))

    TEST_ASSERT(insertGift(sellingRecordset2, 2))
    SellingRecord* newSellingRecord = GetById(SellingRecord, SELLING_RECORD, Database_size(SELLING_RECORD));
    TEST_ASSERT_EQUAL(newSellingRecord->status, SELLING_GIFT);
    TEST_ASSERT_EQUAL(newSellingRecord->partId, 2);

    TEST_ASSERT(insertGift(sellingRecordset3, 3))
    newSellingRecord = GetById(SellingRecord, SELLING_RECORD, Database_size(SELLING_RECORD));
    TEST_ASSERT_EQUAL(newSellingRecord->status, SELLING_GIFT);
    TEST_ASSERT_EQUAL(newSellingRecord->partId, 1);

    TEST_ASSERT(!insertGift(sellingRecordset4, 4))


}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);

    DataManager_finalize();

    return UNITY_END();
}