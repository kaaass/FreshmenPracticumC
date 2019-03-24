//
// Created by guyis on 2019/3/24.
//
#include <stdio.h>
#include "unity.h"

#include "../data/Serializer.h"
#include "../util/StringUtil.h"
#include "../util/Time.h"

#define EQ(a,b) compareString((a), (b)) == STRING_EQUAL

cJSON *data = NULL;

void loadJsonFromFile() {
    FILE *f = fopen("inputs/TestSerializer.json", "r");
    stringbuf content = $init$, line;
    char rawLine[200];
    if (f == NULL) return;
    while (!feof(f)) {
        fgets(rawLine, 200 - 1, f);
        line = STRING(rawLine);
        freeAssign(&content, concat2(content, line));
    }
    data = cJSON_Parse(U8_CSTR(content));
    if (data == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
    $STR_BUF(content);
}

void test_time() {
    cJSON *testData, *timeJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_time");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Time test = Time_parseTime(1553011000);
    string expected, json;
    timeJson = Serialize(Time, test);
    json = STRING(cJSON_Print(timeJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Time: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(timeJson);
    // 反序列化
    stringbuf formatTime;
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "time");
    Time parsedTime = Deserialize(Time, parsed);
    formatTime = Time_toLocalString(parsedTime);
    printf("Deserialize Time: %s\n", CSTR(formatTime));
    TEST_ASSERT(Time_isValid(parsedTime));
    TEST_ASSERT_EQUAL_INT(1553011000, parsedTime.timeStamp);
    $STR_BUF(formatTime);
}

int main() {
    UNITY_BEGIN();
    loadJsonFromFile();

    RUN_TEST(test_time);

    cJSON_Delete(data);
    return UNITY_END();
}
