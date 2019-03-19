//
// Created by guyis on 2019/3/19.
//
#include "unity.h"

#include "../core/Database.h"
#include "../data/TableConfig.h"
#include "../data/DataManager.h"
#include "../data/TableMountings.h"
#include "../data/TablePurchaseRecord.h"


void test_init() {
    DataManager_init();
    TEST_ASSERT_MESSAGE( CONFIG != NULL , "Fail to create database.");
}

void test_table_config() {
    Database *db = Create(Config);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    Config conf[] = {{1, LITERAL("key1"), LITERAL("value1")},
                     {2, LITERAL("key2"), LITERAL("value2")}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Config, &conf[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        Config *now = GetData(Config, cur);
        printf("Config {Id = %d, key = %s, value = %s}\n", now->id, CSTR(now->key), CSTR(now->value));
    }
    Database_destroy(db);
}

void test_table_mountings() {
    Database *db = Create(Mountings);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    Mountings mounts[] = {{.id = 1, .type = MOUNTINGS_KEYBOARD, .sellerId = 1, .name = LITERAL("keyboard1"), .amount = 5, .giftPriority = 2, .price = 57.2},
                     {.id = 2, .type = MOUNTINGS_MOUSE, .sellerId = 2, .name = LITERAL("mouse1"), .amount = 10, .giftPriority = 3, .price = 233.3}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Mountings, &mounts[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        Mountings *now = GetData(Mountings, cur);

        printf("Mountings {id = %d, type = %d, sellerId = %d, name = %s, amount = %d, giftPriority = %d, price = %.2lf}\n",
                now->id, now->type, now->sellerId, CSTR(now->name), now->amount, now->giftPriority, now->price);
    }
    Database_destroy(db);
}

void test_table_purchaseRecord() {
    Database *db = Create(Mountings);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    PurchaseRecord records[] = {{.id=1, .partId = 2, .sellerId = 3, .amount = 4, .total = 5.6, .orderId = 7, .status = PURCHASE_NORMAL, .time = NULL},
                          {.id = 8, .partId = 9, .sellerId = 10, .amount = 11, .total = 12.13, .orderId = 14, .status = PURCHASE_DELETED, .time = NULL}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Mountings, &records[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        PurchaseRecord *now = GetData(PurchaseRecord, cur);

        printf("PurchaseRecord {id = %d, partId = %d, sellerId = %d, amount = %d, total = %.2f, orderId = %d, status = %d,}\n",
               now->id, now->partId, now->sellerId, now->amount, now->total, now->orderId, now->status);
    }
    Database_destroy(db);
}

int main () {
    UNITY_BEGIN();

    RUN_TEST(test_init);
    RUN_TEST(test_table_config);
    RUN_TEST(test_table_mountings);
    RUN_TEST(test_table_purchaseRecord);

    return UNITY_END();
}