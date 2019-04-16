//
// Created by guyis on 2019/4/2.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Config.h"
#include "../util/StringUtil.h"
#include "../core/Database.h"
#include "../data/DataManager.h"
#include "../data/TableConfig.h"
#include "../util/MemoryUtil.h"

/**
 * 设置字符串配置
 *
 * 若不存在则添加新配置
 * @param key
 * @param value
 */
void Config_setString(string key, string value) {
    // 查重
    ForEach(cur, CONFIG) {
        Config *data = GetData(Config, cur);
        if (EQUAL(key, data->key)) {
            $STR_BUF(data->value);
            data->value = cloneString(value);
            return;
        }
    }
    // 添加
    Config data = {
            .key = cloneString(key),
            .value = cloneString(value)
    };
    Database_pushBack(CONFIG, Data(Config, &data));
}

/**
 * 获取字符串配置
 * @param key
 * @param defVal 若不存在，则返回
 * @return
 */
stringbuf Config_optString(string key, string defVal) {
    ForEach(cur, CONFIG) {
        Config *data = GetData(Config, cur);
        if (EQUAL(key, data->key)) {
            return data->value;
        }
    }
    return defVal;
}

/**
 * 设置整数配置
 *
 * 若不存在则添加新配置
 * @param key
 * @param value
 */
void Config_setInteger(string key, int value) {
    char buf[20];
    sprintf(buf, "%d", value);
    Config_setString(key, STRING(buf));
}

/**
 * 设置浮点数配置
 *
 * 若不存在则添加新配置
 * @param key
 * @param value
 */
void Config_setDouble(string key, double value) {
    char buf[20];
    sprintf(buf, "%f", value);
    Config_setString(key, STRING(buf));
}

/**
 * 获取整数配置
 * @param key
 * @param defVal 若不存在，则返回
 * @return
 */
int Config_optInteger(string key, int defVal) {
    int intVal;

    string data = Config_optString(key, $init$);
    if (EQUAL($init$, data))
        return defVal;
    sscanf(CSTR(data), "%d", &intVal);
    return intVal;
}

/**
 * 获取浮点数配置
 * @param key
 * @param defVal 若不存在，则返回
 * @return
 */
double Config_optDouble(string key, double defVal) {
    double doubleVal;

    string data = Config_optString(key, $init$);
    if (EQUAL($init$, data))
        return defVal;
    sscanf(CSTR(data), "%lf", &doubleVal);
    return doubleVal;
}

/**
 * 设置Json配置
 * @param key
 * @param value
 */
void Config_setJson(string key, cJSON *value) {
    assert(value);
    string json = STRING(cJSON_PrintUnformatted(value));
    Config_setString(key, json);
}

/**
 * 获取Json配置，不存在返回NULL
 * @param key
 * @return
 */
cJSON *Config_getJson(string key) {
    string ret = Config_optString(key, $init$);
    if (length(ret) < 1)
        return NULL;
    return cJSON_Parse(U8_CSTR(ret));
}

/**
 * 设置整数数组配置
 * @param key
 * @param arr 整数数组
 * @param n 数组长度
 */
void Config_setIntArray(string key, int* arr, int n) {
    assert(arr);
    cJSON *json = cJSON_CreateIntArray(arr, n);
    Config_setJson(key, json);
    cJSON_Delete(json);
}

/**
 * 获取整数数组配置
 * @param key
 * @param len
 * @return 数组首指针，数组长度见Config_getIntArrayLen
 */
int *Config_getIntArray(string key, int *len) {
    cJSON *json = Config_getJson(key);
    *len = 0;
    if (json == NULL)
        return NULL;
    if (!cJSON_IsArray(json))
        return NULL;
    *len = cJSON_GetArraySize(json);
    int* arr = (int *) malloc(sizeof(int) * *len);
    for (int i = 0; i < *len; i++) {
        arr[i] = cJSON_GetArrayItem(json, i)->valueint;
    }
    return arr;
}
