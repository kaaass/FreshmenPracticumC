//
// Created by guyis on 2019/3/19.
//

#include "../util/FileUtil.h"
#include "TableConfig.h"
#include "Serializer.h"
#include "DataManager.h"
#include "TableOrder.h"
#include "TableProvider.h"
#include "TableMountings.h"
#include "TablePurchaseRecord.h"
#include "TableGuest.h"
#include "TableSellingRecord.h"

Database *CONFIG;
Database *GUEST;
Database *SELLING_RECORD;
Database *ORDER;
Database *PROVIDER;
Database *MOUNTINGS;
Database *PURCHASE_RECORD;

/**
 * 初始化DataManager
 */
void DataManager_init() {
    CONFIG = Create(Config);
    GUEST = Create(Guest);
    SELLING_RECORD = Create(SellingRecord);
    ORDER = Create(Order);
    PROVIDER = Create(Provider);
    MOUNTINGS = Create(Mountings);
    PURCHASE_RECORD = Create(PurchaseRecord);
}

/**
 * DataManager析构
 */
void DataManager_finalize() {
    Database_destroy(CONFIG);
    Database_destroy(GUEST);
    Database_destroy(SELLING_RECORD);
    Database_destroy(ORDER);
    Database_destroy(PROVIDER);
    Database_destroy(MOUNTINGS);
    Database_destroy(PURCHASE_RECORD);
}

/**
 * 将当前数据库保存至文件
 * @param dir 路径，不包含'/'
 */
void DataManager_save(string dir) {
    cJSON *json;
    stringbuf path, content;
    MKDIR(CSTR(dir));
    // Config
    path = LITERAL("/Config.json");
    path = concat(2, dir, path);
    json = SerializeDB(Config, CONFIG);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Guest
    path = LITERAL("/Guest.json");
    path = concat(2, dir, path);
    json = SerializeDB(Guest, GUEST);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // SellingRecord
    path = LITERAL("/SellingRecord.json");
    path = concat(2, dir, path);
    json = SerializeDB(SellingRecord, SELLING_RECORD);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Order
    path = LITERAL("/Order.json");
    path = concat(2, dir, path);
    json = SerializeDB(Order, ORDER);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Provider
    path = LITERAL("/Provider.json");
    path = concat(2, dir, path);
    json = SerializeDB(Provider, PROVIDER);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Mountings
    path = LITERAL("/Mountings.json");
    path = concat(2, dir, path);
    json = SerializeDB(Mountings, MOUNTINGS);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
    // PurchaseRecord
    path = LITERAL("/PurchaseRecord.json");
    path = concat(2, dir, path);
    json = SerializeDB(PurchaseRecord, PURCHASE_RECORD);
    content = STRING(cJSON_Print(json));
    writeStringToFile(CSTR(path), content);
    cJSON_Delete(json);
    $STR_BUF(path);
}

/**
 * 从文件读入当前数据库
 * @param dir 路径，不包含'/'
 */
void DataManager_load(string dir) {
    cJSON *json;
    stringbuf path, content;
    // Config
    path = LITERAL("/Config.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Config, CONFIG, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Guest
    path = LITERAL("/Guest.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Guest, GUEST, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // SellingRecord
    path = LITERAL("/SellingRecord.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(SellingRecord, SELLING_RECORD, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Order
    path = LITERAL("/Order.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Order, ORDER, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Provider
    path = LITERAL("/Provider.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Provider, PROVIDER, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // Mountings
    path = LITERAL("/Mountings.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Mountings, MOUNTINGS, json);
    cJSON_Delete(json);
    $STR_BUF(path);
    // PurchaseRecord
    path = LITERAL("/PurchaseRecord.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(PurchaseRecord, PURCHASE_RECORD, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}