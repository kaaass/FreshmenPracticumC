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

cJSON *serialize_Guest(Guest g) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", g.id);
    cJSON_AddStringToObject(json, "name", g.name);
    cJSON_AddStringToObject(json, "phone", g.phone);
    return json;
}

Guest deserialize_Guest(const cJSON *json) {
    Guest g;
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *phone = cJSON_GetObjectItem(json, "phone");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        g.id = id->valueint;
    }
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        g.name = name->valuestring;
    }
    if (cJSON_IsString(phone) && (phone->valuestring != NULL)) {
        g.phone = phone->valuestring;
    }
    return g;
}