//
// Created by guyis on 2019/4/2.
//
#include <stdio.h>
#include <stdlib.h>

#include "Config.h"
#include "../util/StringUtil.h"
#include "../core/Database.h"
#include "../data/DataManager.h"
#include "../data/TableConfig.h"

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
    Config_setString(key, newString(buf));
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
