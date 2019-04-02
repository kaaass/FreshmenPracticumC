//
// Created by guyis on 2019/3/14.
//
#include "unity.h"

#include "../core/Database.h"
#include "TableTest.h"

Database *db = NULL;

void test_create_database() {
    db = Create(Test);
    TEST_ASSERT_MESSAGE(db != NULL, "Fail to create database.");
}

void test_pushData() {
    Test sigle = {.num = 114,
            .str = STR_BUF("SingleLine")};
    Database_pushBack(db, Data(Test, &sigle));
    TEST_ASSERT_EQUAL_INT(1, Database_size(db));

    Test data[] = {
            {.num = 233,
                    .str = STR_BUF("test")},
            {.num = 666,
                    .str = STR_BUF("test2")}
    };
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, Data(Test, &data[i]));
    }
    TEST_ASSERT_EQUAL_INT(3, Database_size(db));
}

void test_cursor() {
    Cursor *cur = Database_begin(db);
    TEST_ASSERT(CheckType(Test, cur))
    DataNode *next = cur->cur->next;
    Cursor_next(cur);
    TEST_ASSERT(CheckType(Test, cur))
    TEST_ASSERT(cur->cur == next);
}

void test_get_by_id() {
    Test *test;
    test = GetById(Test, db, 1);
    TEST_ASSERT_EQUAL_INT(114, test->num);
    test = GetById(Test, db, 2);
    TEST_ASSERT_EQUAL_INT(233, test->num);
    test = GetById(Test, db, 3);
    TEST_ASSERT_EQUAL_INT(666, test->num);
}

void test_foreach() {
    int cnt = 0;
    ForEach(cur, db) {
        Test *record = GetData(Test, cur);
        printf("Id %d: Num = %d, Str = %s.\n", record->id, record->num, CSTR(record->str));
        TEST_ASSERT_EQUAL_INT(++cnt, record->id);
        $STR_BUF(record->str);
    }
    TEST_ASSERT_EQUAL_INT(Database_size(db), cnt);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_create_database);
    RUN_TEST(test_pushData);
    RUN_TEST(test_cursor);
    RUN_TEST(test_get_by_id);
    RUN_TEST(test_foreach); // 需要是最后一个以释放字符串

    Database_destroy(db);

    return UNITY_END();
}
