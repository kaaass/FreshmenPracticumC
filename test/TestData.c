//
// Created by guyis on 2019/3/19.
//
#include "unity.h"

#include "../core/Database.h"
#include "../data/TableConfig.h"
#include "../data/DataManager.h"
#include "../data/TableGuest.h"
#include "../data/TableSellingRecord.h"

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

void test_table_guest(){
    Database *db = Create(Guest);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    Guest conf[] = {
            {1,LITERAL("name1"),LITERAL("phone1")},
            {2,LITERAL("name2"),LITERAL("phone2")}
    };
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Guest, &conf[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        Guest *now = GetData(Guest, cur);
        printf("Guest {Id = %d, name = %s, phone = %s}\n", now->id, CSTR(now->name), CSTR(now->phone));
    }
    Database_destroy(db);
}

void test_table_selling_record(){
    Database *db = Create(SellingRecord);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    SellingRecord conf[] = {
            {.id = 1,.partId = 1,.status  = 1,.guestId = 1,.amount = 1,.total = 1,.time = NULL,.giftId = 1,.orderId = 1},
            {.id = 2,.partId = 2,.status  = 2,.guestId = 2,.amount = 2,.total = 2,.time = NULL,.giftId = 2,.orderId = 2}
    };
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(SellingRecord, &conf[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        SellingRecord *now = GetData(SellingRecord, cur);
        printf("Selling Record {Id = %d, partId = %d, status = %d, guestId = %d,amount = %d,total = %f,giftId = %d,orderId = %d}\n",now->id ,now->partId ,
                now->status ,now->guestId ,now->amount ,now->total,now->giftId,now->orderId);
    }
    Database_destroy(db);
}

int main () {
    UNITY_BEGIN();

    RUN_TEST(test_init);
    RUN_TEST(test_table_config);
    RUN_TEST(test_table_guest);
    RUN_TEST(test_table_selling_record);
    return UNITY_END();
}