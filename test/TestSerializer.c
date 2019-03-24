//
// Created by guyis on 2019/3/24.
//
#include <stdio.h>
#include "unity.h"

#include "../data/Serializer.h"
#include "../util/StringUtil.h"
#include "../util/Time.h"
#include "../data/TableConfig.h"
#include "../data/TableGuest.h"
#include "../data/TableMountings.h"
#include "../data/TableOrder.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableProvider.h"
#include "../data/TableSellingRecord.h"

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

void test_guest() {
    cJSON *testData, *guestJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_guest");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Guest test = {.id = 5, .name = "kenneth", .phone = "233-233-2233"};
    string expected, json;
    guestJson = Serialize(Guest, test);
    json = STRING(cJSON_Print(guestJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Guest: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(guestJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "guest");
    Guest parsedGuest = Deserialize(Guest, parsed);
    printf("Deserialize Guest: id = %d, name = %s, phone = %s\n", parsedGuest.id, CSTR(parsedGuest.name), CSTR(parsedGuest.phone));
    TEST_ASSERT_EQUAL_INT(5, parsedGuest.id);
    TEST_ASSERT_EQUAL("kenneth", parsedGuest.name);
    TEST_ASSERT_EQUAL("233-233-2233", parsedGuest.phone);
}

void test_provider() {
    cJSON *testData, *providerJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_provider");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Provider test = {.id = 15, .name = "kevin", .phone = "123-321-1234567"};
    string expected, json;
    providerJson = Serialize(Provider, test);
    json = STRING(cJSON_Print(providerJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Provider: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(providerJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "provider");
    Provider parsedProvider = Deserialize(Provider, parsed);
    printf("Deserialize Provider: id = %d, name = %s, phone = %s\n", parsedProvider.id, CSTR(parsedProvider.name), CSTR(parsedProvider.phone));
    TEST_ASSERT_EQUAL_INT(15, parsedProvider.id);
    TEST_ASSERT_EQUAL("kevin", parsedProvider.name);
    TEST_ASSERT_EQUAL("123-321-1234567", parsedProvider.phone);
}

void test_config() {
    cJSON *testData, *configJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_config");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Config test = {.id = 516, .key = "ys", .value = "tql"};
    string expected, json;
    configJson = Serialize(Config, test);
    json = STRING(cJSON_Print(configJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Config: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(configJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "config");
    Config parsedConfig = Deserialize(Config, parsed);
    printf("Deserialize Config: id = %d, key = %s, value = %s\n", parsedConfig.id, CSTR(parsedConfig.key), CSTR(parsedConfig.value));
    TEST_ASSERT_EQUAL_INT(516, parsedConfig.id);
    TEST_ASSERT_EQUAL("ys", parsedConfig.key);
    TEST_ASSERT_EQUAL("tql", parsedConfig.value);
}

void test_mountings() {
    cJSON *testData, *mountingsJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_mountings");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Mountings test = {.id = 7596, .type = 1, .sellerId = 1561, .name = "gugugu", .amount = 797, .giftPriority = 4, .price = 45.67};
    string expected, json;
    mountingsJson = Serialize(Mountings, test);
    json = STRING(cJSON_Print(mountingsJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Mountings: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(mountingsJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "mountings");
    Mountings parsedMountings = Deserialize(Mountings, parsed);
    printf("Deserialize Mountings: id = %d, type = %d, sellerId = %d, name = %s, amount = %d, giftPriority = %d, price = %f\n", parsedMountings.id, parsedMountings.type, parsedMountings.sellerId, CSTR(parsedMountings.name), parsedMountings.amount, parsedMountings.giftPriority, parsedMountings.price);
    TEST_ASSERT_EQUAL_INT(7596, parsedMountings.id);
    TEST_ASSERT_EQUAL_INT(1, parsedMountings.type);
    TEST_ASSERT_EQUAL_INT(1561, parsedMountings.sellerId);
    TEST_ASSERT_EQUAL("gugugu", parsedMountings.name);
    TEST_ASSERT_EQUAL_INT(797, parsedMountings.amount);
    TEST_ASSERT_EQUAL_INT(4, parsedMountings.giftPriority);
    TEST_ASSERT_EQUAL_FLOAT(45.67, parsedMountings.price);
}

void test_order() {
    cJSON *testData, *orderJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_order");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    int opId[MAX_OP_ID] = {45,56,67}
    Order test = {.id = 61, .type = 4, .status = 2, .opCount = 3, .opId = opId, .price = 53.21};
    string expected, json;
    orderJson = Serialize(Order, test);
    json = STRING(cJSON_Print(orderJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize Order: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(orderJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "order");
    Order parsedOrder = Deserialize(Order, parsed);
    printf("Deserialize Order: id = %d, type = %d, status = %d, opCount = %d, opId:[", parsedOrder.id, parsedOrder.type, parsedOrder.status, parsedOrder.opCount);
    printf("%d", parsedOrder.opId[0]);
    for (int i = 1; i < parsedOrder.opCount; ++i) {
        printf(",%d", parsedOrder.opId[i]);
    }
    printf("], price = %f", parsedOrder.price);
    TEST_ASSERT_EQUAL_INT(61, parsedOrder.id);
    TEST_ASSERT_EQUAL_INT(4, parsedOrder.type);
    TEST_ASSERT_EQUAL_INT(2, parsedOrder.status);
    TEST_ASSERT_EQUAL_INT(3, parsedOrder.opCount);
    TEST_ASSERT_EQUAL_INT(45, parsedOrder.opId[0]);
    TEST_ASSERT_EQUAL_INT(56, parsedOrder.opId[1]);
    TEST_ASSERT_EQUAL_INT(67, parsedOrder.opId[2]);
    TEST_ASSERT_EQUAL_FLOAT(53.21, parsedOrder.price);
}

void test_purchaseRecord() {
    cJSON *testData, *purchaseRecordJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_purchase_record");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Time time = Time_parseTime(1553011022);
    PurchaseRecord test = {.id = 654, .partId = 641, .amount = 461, .total = 87562.54, .orderId = 13434, .status = 4, .time = time};
    string expected, json;
    purchaseRecordJson = Serialize(PurchaseRecord, test);
    json = STRING(cJSON_Print(purchaseRecordJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize PurchaseRecord: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(purchaseRecordJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "purchase_record");
    PurchaseRecord parsedPurchaseRecord = Deserialize(PurchaseRecord, parsed);
    printf("Deserialize PurchaseRecord: id = %d, partId = %d, sellerId = %d, amount = %d, total = %f, orderId = %d, status = %d, time = %s", parsedPurchaseRecord.id, parsedPurchaseRecord.partId, parsedPurchaseRecord.sellerId, parsedPurchaseRecord.amount, parsedPurchaseRecord.total, parsedPurchaseRecord.orderId,parsedPurchaseRecord.status, CSTR(Time_toLocalString(parsedPurchaseRecord.time)));
    TEST_ASSERT_EQUAL_INT(654, parsedPurchaseRecord.id);
    TEST_ASSERT_EQUAL_INT(641, parsedPurchaseRecord.partId);
    TEST_ASSERT_EQUAL_INT(4864, parsedPurchaseRecord.sellerId);
    TEST_ASSERT_EQUAL_INT(461, parsedPurchaseRecord.amount);
    TEST_ASSERT_EQUAL_FLOAT(87562.54, parsedPurchaseRecord.total);
    TEST_ASSERT_EQUAL_INT(13434, parsedPurchaseRecord.orderId);
    TEST_ASSERT_EQUAL_INT(4, parsedPurchaseRecord.status);
    TEST_ASSERT_EQUAL("1553011022", Time_toLocalString(parsedPurchaseRecord.time));
}

void test_sellerRecord() {
    cJSON *testData, *sellerRecordJson, *parsed;
    testData = cJSON_GetObjectItemCaseSensitive(data, "test_seller_record");
    // 开始测试
    // 序列化
    cJSON *expectedJson;
    Time time = Time_parseTime(1553011044);
    SellingRecord test = {.id = 615, .partId = 6168, .status = 1, .guestId = 616115, .amount = 6111, .total = 97.79, .time = time, .giftId = 6161616, .orderId = 619191};
    string expected, json;
    sellerRecordJson = Serialize(SellerRecord, test);
    json = STRING(cJSON_Print(sellerRecordJson));
    expectedJson = cJSON_GetObjectItemCaseSensitive(testData, "expected");
    expected = STRING(expectedJson->valuestring);
    printf("Serialize SellerRecord: %s\n", CSTR(json));
    TEST_ASSERT(EQ(expected, json));
    cJSON_Delete(sellerRecordJson);
    // 反序列化
    parsed = cJSON_GetObjectItemCaseSensitive(testData, "seller_record");
    SellingRecord parsedSellerRecord = Deserialize(SellingRecord, parsed);
    printf("Deserialize SellerRecord: id = %d, partId = %d, status = %d, guestId = %d, amount = %d, total = %f, time = %s, giftId = %d, orderId = %d\n", parsedSellerRecord.id, parsedSellerRecord.partId, parsedSellerRecord.status, parsedSellerRecord.guestId, parsedSellerRecord.amount, parsedSellerRecord.total, CSTR(Time_toLocalString(parsedSellerRecord.time)), parsedSellerRecord.giftId, parsedSellerRecord.orderId);
    TEST_ASSERT_EQUAL_INT(615, parsedSellerRecord.id);
    TEST_ASSERT_EQUAL_INT(6168, parsedSellerRecord.partId);
    TEST_ASSERT_EQUAL_INT(1, parsedSellerRecord.status);
    TEST_ASSERT_EQUAL_INT(616115, parsedSellerRecord.guestId);
    TEST_ASSERT_EQUAL_INT(6111, parsedSellerRecord.amount);
    TEST_ASSERT_EQUAL_FLOAT(97.79, parsedSellerRecord.total);
    TEST_ASSERT_EQUAL("1553011044", Time_toLocalString(parsedSellerRecord.time));
    TEST_ASSERT_EQUAL_INT(6161616, parsedSellerRecord.giftId);
    TEST_ASSERT_EQUAL_INT(619191, parsedSellerRecord.orderId);
}

int main() {
    UNITY_BEGIN();
    loadJsonFromFile();

    RUN_TEST(test_time);
    RUN_TEST(test_guest);
    RUN_TEST(test_provider);
    RUN_TEST(test_config);
    RUN_TEST(test_mountings);
    RUN_TEST(test_order);
    RUN_TEST(test_purchaseRecord);
    RUN_TEST(test_sellerRecord);

    cJSON_Delete(data);
    return UNITY_END();
}
