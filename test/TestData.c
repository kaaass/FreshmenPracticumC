//
// Created by guyis on 2019/3/19.
//
#include "unity.h"

#include "../core/Database.h"
#include "../data/TableConfig.h"

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

int main () {
    UNITY_BEGIN();

    RUN_TEST(test_table_config);

    return UNITY_END();
}