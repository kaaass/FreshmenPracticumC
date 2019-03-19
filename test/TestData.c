//
// Created by guyis on 2019/3/19.
//
#include "unity.h"

#include "../core/Database.h"
#include "../data/TableConfig.h"
#include "../data/DataManager.h"
#include "../data/TableOrder.h"
#include "../data/TableProvider.h"

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
void test_table_order(){
    Database *db = Create(Order);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    Order conf[] = {{1,0,0,0,{0},0},
                    {2,0,0,0,{0},0}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Order, &conf[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        Order *now = GetData(Order, cur);
        printf("Config {Id = %d, type = %d, status = %d}\n", now->id, now->type, now->status);
    }
    Database_destroy(db);
}
void test_table_provider(){
    Database *db = Create(Provider);
    TEST_ASSERT_MESSAGE( db != NULL , "Fail to create database.");
    Provider conf[] = {{1,LITERAL("key1"),LITERAL("value1")},
                       {2,LITERAL("key2"),LITERAL("value2")}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Provider, &conf[i]));
        TEST_ASSERT_EQUAL_INT(i + 1, Database_size(db));
    }
    ForEach(cur, db) {
        Provider *now = GetData(Provider, cur);
        printf("Config {Id = %d, name = %s, phone = %s}\n", now->id, CSTR(now->name), CSTR(now->phone));
    }
    Database_destroy(db);


}
int main () {
    UNITY_BEGIN();

    RUN_TEST(test_init);
    RUN_TEST(test_table_order);
    RUN_TEST(test_table_provider);

    return UNITY_END();
}