#include <stdio.h>

#include "core/Database.h"
#include "core/TableTest.h"

int main() {
    Database *db = Create(Test);
    Test data[] = {{1, 233, "test"},
                    {2, 666, "test2"}};
    for (int i = 0; i < 2; i++) {
        Database_pushBack(db, &data[i]);
    }
    ForEach(cur, db) {
        Test *record = GetData(Test, cur);
        printf("Id %d: Num = %d, Str = %s.\n", record->id, record->num, record->str);
    }
    Database_destroy(db);
    return 0;
}