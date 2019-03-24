//
// Created by guyis on 2019/3/24.
//
#include <assert.h>
#include "Serializer.h"

cJSON *serialize_Time(Time t) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "ts", t.timeStamp);
    return json;
}

cJSON *serialize_Guest(Guest g) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", g.id);
    cJSON_AddStringToObject(json, "name", U8_CSTR(g.name));
    cJSON_AddStringToObject(json, "phone", U8_CSTR(g.phone));
    return json;
}

cJSON *serialize_Provider(Provider p) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", p.id);
    cJSON_AddStringToObject(json, "name", U8_CSTR(p.name));
    cJSON_AddStringToObject(json, "phone", U8_CSTR(p.phone));
    return json;
}

cJSON *serialize_Config(Config config) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", config.id);
    cJSON_AddStringToObject(json, "key", U8_CSTR(config.key));
    cJSON_AddStringToObject(json, "value", U8_CSTR(config.value));
    return json;
}

cJSON *serialize_Mountings(Mountings mountings) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", mountings.id);
    cJSON_AddNumberToObject(json, "type", mountings.type);
    cJSON_AddNumberToObject(json, "sellerId", mountings.sellerId);
    cJSON_AddStringToObject(json, "name", U8_CSTR(mountings.name));
    cJSON_AddNumberToObject(json, "amount", mountings.amount);
    cJSON_AddNumberToObject(json, "giftPriority", mountings.giftPriority);
    cJSON_AddNumberToObject(json, "price", mountings.price);
    return json;
}

cJSON *serialize_Order(Order order) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", order.id);
    cJSON_AddNumberToObject(json, "type", order.type);
    cJSON_AddNumberToObject(json, "status", order.status);
    cJSON *ops = cJSON_CreateArray();
    cJSON *num;
    assert(ops);
    for (int i = 0; i < order.opCount; ++i) {
        num = cJSON_CreateNumber(order.opId[i]);
        cJSON_AddItemToArray(ops, num);
    }
    cJSON_AddItemToObject(json, "ops", ops);
    cJSON_AddNumberToObject(json, "price", order.price);
    return json;
}

cJSON *serialize_PurchaseRecord(PurchaseRecord pr) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", pr.id);
    cJSON_AddNumberToObject(json, "partId", pr.partId);
    cJSON_AddNumberToObject(json, "sellerId", pr.sellerId);
    cJSON_AddNumberToObject(json, "amount", pr.amount);
    cJSON_AddNumberToObject(json, "total", pr.total);
    cJSON_AddNumberToObject(json, "orderId", pr.orderId);
    cJSON_AddNumberToObject(json, "status", pr.status);
    cJSON_AddItemToObject(json, "time", serialize_Time(pr.time));
    return json;
}

cJSON *serialize_SellingRecord(SellingRecord sr) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", sr.id);
    cJSON_AddNumberToObject(json, "partId", sr.partId);
    cJSON_AddNumberToObject(json, "status", sr.status);
    cJSON_AddNumberToObject(json, "guestId", sr.guestId);
    cJSON_AddNumberToObject(json, "amount", sr.amount);
    cJSON_AddNumberToObject(json, "total", sr.total);
    cJSON_AddItemToObject(json, "time", serialize_Time(sr.time));
    cJSON_AddNumberToObject(json, "giftId", sr.giftId);
    cJSON_AddNumberToObject(json, "orderId", sr.orderId);
}


Time deserialize_Time(const cJSON *json) {
    Time t = {.timeStamp = -1};
    cJSON *ts = cJSON_GetObjectItem(json, "ts");
    if (cJSON_IsNumber(ts) && ts->valueint != -1) {
        t = Time_parseTime(ts->valueint);
    }
    return t;
}

Guest deserialize_Guest(const cJSON *json) {
    Guest guest = {
            .id = -1,
            .name = $init$,
            .phone = $init$
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *phone = cJSON_GetObjectItem(json, "phone");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        guest.id = id->valueint;
    }
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        freeAssign(&guest.name, newString(name->valuestring));
    }
    if (cJSON_IsString(phone) && (phone->valuestring != NULL)) {
        freeAssign(&guest.phone, newString(phone->valuestring));
    }
    return guest;
}

Provider deserialize_Provider(const cJSON *json) {
    Provider provider = {
            .id = -1,
            .name = $init$,
            .phone = $init$
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *phone = cJSON_GetObjectItem(json, "phone");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        provider.id = id->valueint;
    }
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        freeAssign(&provider.name, newString(name->valuestring));
    }
    if (cJSON_IsString(phone) && (phone->valuestring != NULL)) {
        freeAssign(&provider.phone, newString(phone->valuestring));
    }
    return provider;
}

Config deserialize_Config(const cJSON *json) {
    Config config = {
            .id = -1,
            .key = $init$,
            .value = $init$
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *key = cJSON_GetObjectItem(json, "key");
    cJSON *value = cJSON_GetObjectItem(json, "value");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        config.id = id->valueint;
    }
    if (cJSON_IsString(key) && (key->valuestring != NULL)) {
        freeAssign(&config.key, newString(key->valuestring));
    }
    if (cJSON_IsString(value) && (value->valuestring != NULL)) {
        freeAssign(&config.value, newString(value->valuestring));
    }
    return config;
}

Mountings deserialize_Mountings(const cJSON *json) {
    Mountings mountings = {
            .id = -1,
            .name = $init$
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *type = cJSON_GetObjectItem(json, "type");
    cJSON *sellerId = cJSON_GetObjectItem(json, "sellerId");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *amount = cJSON_GetObjectItem(json, "amount");
    cJSON *giftPriority = cJSON_GetObjectItem(json, "giftPriority");
    cJSON *price = cJSON_GetObjectItem(json, "price");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        mountings.id = id->valueint;
    }
    if (cJSON_IsNumber(type)) {
        mountings.type = type->valueint;
    }
    if (cJSON_IsNumber(sellerId)) {
        mountings.sellerId = sellerId->valueint;
    }
    if (cJSON_IsString(name) && name->valuestring != NULL) {
        freeAssign(&mountings.name, newString(name->valuestring));
    }
    if (cJSON_IsNumber(amount)) {
        mountings.amount = amount->valueint;
    }
    if (cJSON_IsNumber(giftPriority)) {
        mountings.giftPriority = giftPriority->valueint;
    }
    if (cJSON_IsNumber(price)) {
        mountings.price = price->valuedouble;
    }
    return mountings;
}

Order deserialize_Order(const cJSON *json) {
    Order order = {
            .id = -1
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *type = cJSON_GetObjectItem(json, "type");
    cJSON *status = cJSON_GetObjectItem(json, "status");
    cJSON *ops = cJSON_GetObjectItem(json, "ops");
    cJSON *price = cJSON_GetObjectItem(json, "price");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        order.id = id->valueint;
    }
    if (cJSON_IsNumber(type)) {
        order.type = type->valueint;
    }
    if (cJSON_IsNumber(status)) {
        order.status = status->valueint;
    }
    if (cJSON_IsNumber(price)) {
        order.price = price->valueint;
    }
    // 解析ops数组
    cJSON *opId;
    int cnt = 0;
    if (cJSON_IsArray(ops)) {
        cJSON_ArrayForEach(opId, ops) {
            if (cJSON_IsNumber(opId)) {
                order.opId[cnt++] = opId->valueint;
            }
        }
        assert(cJSON_GetArraySize(ops) == cnt);
        order.opCount = cnt;
    }
    return order;
}

PurchaseRecord deserialize_PurchaseRecord(const cJSON *json) {
    PurchaseRecord purchaseRecord = {
            .id = -1
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *partId = cJSON_GetObjectItem(json, "partId");
    cJSON *amount = cJSON_GetObjectItem(json, "amount");
    cJSON *total = cJSON_GetObjectItem(json, "total");
    cJSON *orderId = cJSON_GetObjectItem(json, "orderId");
    cJSON *status = cJSON_GetObjectItem(json, "status");
    cJSON *time = cJSON_GetObjectItem(json, "time");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        purchaseRecord.id = id->valueint;
    }
    if (cJSON_IsNumber(partId)) {
        purchaseRecord.partId = partId->valueint;
    }
    if (cJSON_IsNumber(amount)) {
        purchaseRecord.amount = amount->valueint;
    }
    if (cJSON_IsNumber(total)) {
        purchaseRecord.total = amount->valueint;
    }
    if (cJSON_IsNumber(orderId)) {
        purchaseRecord.orderId = orderId->valueint;
    }
    if (cJSON_IsNumber(status)) {
        purchaseRecord.status = status->valueint;
    }
    if (cJSON_IsNumber(total)) {
        purchaseRecord.total = total->valuedouble;
    }
    purchaseRecord.time = deserialize_Time(time);
    return purchaseRecord;

}

SellingRecord deserialize_SellingRecord(const cJSON *json) {
    SellingRecord sellingRecord = {
            .id = -1
    };
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *partId = cJSON_GetObjectItem(json, "partId");
    cJSON *status = cJSON_GetObjectItem(json, "status");
    cJSON *guestId = cJSON_GetObjectItem(json, "guestId");
    cJSON *amount = cJSON_GetObjectItem(json, "amount");
    cJSON *total = cJSON_GetObjectItem(json, "total");
    cJSON *time = cJSON_GetObjectItem(json, "time");
    cJSON *giftId = cJSON_GetObjectItem(json, "giftId");
    cJSON *orderId = cJSON_GetObjectItem(json, "orderId");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        sellingRecord.id = id->valueint;
    }
    if (cJSON_IsNumber(partId)) {
        sellingRecord.partId = partId->valueint;
    }
    if (cJSON_IsNumber(status)) {
        sellingRecord.status = status->valueint;
    }
    if (cJSON_IsNumber(guestId)) {
        sellingRecord.guestId = guestId->valueint;
    }
    if (cJSON_IsNumber(amount)) {
        sellingRecord.amount = amount->valueint;
    }
    if (cJSON_IsNumber(total)) {
        sellingRecord.total = total->valuedouble;
    }
    if (cJSON_IsNumber(giftId) && giftId->valueint != -1) {
        sellingRecord.giftId = giftId->valueint;
    }
    if (cJSON_IsNumber(orderId) && orderId->valueint != -1) {
        sellingRecord.orderId = orderId->valueint;
    }
    sellingRecord.time = deserialize_Time(time);
    return sellingRecord;
}