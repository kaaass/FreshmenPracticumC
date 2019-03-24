//
// Created by guyis on 2019/3/24.
//
#include "Serializer.h"

cJSON *serialize_Time(Time t) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "ts", t.timeStamp);
    return json;
}

Time deserialize_Time(const cJSON *json) {
    Time t = {.timeStamp = -1};
    cJSON *ts = cJSON_GetObjectItem(json, "ts");
    if (cJSON_IsNumber(ts) && ts->valueint != -1) {
        t = Time_parseTime(ts->valueint);
    }
    return t;
}