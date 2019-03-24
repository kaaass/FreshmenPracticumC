//
// Created by guyis on 2019/3/24.
//
#include "Serializer.h"

cJSON *serialize_Time(Time t) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "ts", t.timeStamp);
    return json;
}

cJSON *serialize_Guest(Guest g) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", g.id);
    cJSON_AddStringToObject(json, "name", g.name);
    cJSON_AddStringToObject(json, "phone", g.phone);
    return json;
}

cJSON *serialize_Provider(Provider p) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", p.id);
    cJSON_AddStringToObject(json, "name", p.name);
    cJSON_AddStringToObject(json, "phone", p.phone);
    return json;
}

cJSON *serialize_Config(Config config) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", config.id);
    cJSON_AddStringToObject(json, "key", config.key);
    cJSON_AddStringToObject(json, "value", config.value);
    return json;
}

cJSON *serialize_Mountings(Mountings mountings) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", mountings.id);
    cJSON_AddNumberToObject(json, "type", mountings.type);
    cJSON_AddNumberToObject(json, "sellerId", mountings.sellerId);
    cJSON_AddStringToObject(json, "name", mountings.name);
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
    cJSON_AddNumberToObject(json, "opCount", order.opCount);
    cJSON opId = cJSON_CreateArray();
    cJSON num;
    if (opId != NULL) {
        for (int i = 0; i < order.opCount; ++i) {
            num = cJSON_CreateNumber(order.opId[i]);
            cJSON_AddItemToArray(opId, num);
        }
        cJSON_AddItemToObject(json, "opId", opId);
    }
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

    cJSON *time = serialize_Time(pr.time);
    cJSON_AddItemToObject(json, "time", *time);
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


    cJSON *time = serialize_Time(sr.time);
    cJSON_AddItemToObject(json, "time", *time);

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

Guest deserialize_Provider(const cJSON *json) {
    Provider p;
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *phone = cJSON_GetObjectItem(json, "phone");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        p.id = id->valueint;
    }
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        p.name = name->valuestring;
    }
    if (cJSON_IsString(phone) && (phone->valuestring != NULL)) {
        p.phone = phone->valuestring;
    }
    return p;
}

Config deserialize_Config(const cJSON *json) {
    Config config;
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *key = cJSON_GetObjectItem(json, "key");
    cJSON *value = cJSON_GetObjectItem(json, "value");
    if (cJSON_IsNumber(id) && id->valueint != -1) {
        config.id = id->valueint;
    }
    if (cJSON_IsString(key) && (key->valuestring != NULL)) {
        config.key = key->valuestring;
    }
    if (cJSON_IsString(phone) && (phone->valuestring != NULL)) {
        config.value = value->valuestring;
    }
    return config;
}

Mountings deserialize_Mountings(const cJSON *json) {
    Mountings mountings;
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
    if (cJSON_IsNumber(type) && type->valueint != -1) {
        mountings.type = type->valueint;
    }
    if (cJSON_IsNumber(sellerId) && sellerId->valueint != -1) {
        mountings.sellerId = sellerId->valueint;
    }
    if (cJSON_IsString(name) && name->valuestring != -1) {
        mountings.name = name->valuestring;
    }
    if (cJSON_IsNumber(amount) && amount->valueint != -1) {
        mountings.amount = amount->valueint;
    }
    if (cJSON_IsNumber(giftPriority) && giftPriority->valueint != -1) {
        mountings.giftPriority = giftPriority->valueint;
    }
    if (cJSON_IsNumber(price) && price->valueint != -1) {
        mountings.price = price->valueint;
    }
    return mountings;

}

Order deserialize_Order(const cJSON *json) {
    Order order;
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *type = cJSON_GetObjectItem(json, "type");
    cJSON *status = cJSON_GetObjectItem(json, "status");
    cJSON *opCount = cJSON_GetObjectItem(json, "opCount");
    cJSON *opId = cJSON_GetObjectItem(json, "opId");
    cJSON *price = cJSON_GetObjectItem(json, "price");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        order.id = id->valueint;
    }

    if (cJSON_IsNumber(type) && type->valueint != -1) {
        order.type = type->valueint;
    }

    if (cJSON_IsNumber(status) && status->valueint != -1) {
        order.status = status->valueint;
    }

    if (cJSON_IsNumber(opCount) && opCount->valueint != -1) {
        order.opCount = opCount->valueint;
    }

    cJSON *oid;
    int cnt = 0;
    cJSON_ArrayForEach(oid, opId) {
        order.opId[cnt++] = oid;
    }

    if (cJSON_IsNumber(price) && price->valueint != -1) {
        order.price = price->valueint;
    }

    return order;
}

PurchaseRecord deserialize_PurchaseRecord(const cJSON *json) {
    PurchaseRecord pr;
    cJSON *id = cJSON_GetObjectItem(json, "id");
    cJSON *partId = cJSON_GetObjectItem(json, "partId");
    cJSON *amount = cJSON_GetObjectItem(json, "amount");
    cJSON *total = cJSON_GetObjectItem(json, "total");
    cJSON *orderId = cJSON_GetObjectItem(json, "orderId");
    cJSON *status = cJSON_GetObjectItem(json, "status");
    cJSON *time = cJSON_GetObjectItem(json, "time");

    if (cJSON_IsNumber(id) && id->valueint != -1) {
        pr.id = id->valueint;
    }

    if (cJSON_IsNumber(partId) && partId->valueint != -1) {
        pr.partId = partId->valueint;
    }

    if (cJSON_IsNumber(amount) && amount->valueint != -1) {
        pr.amount = amount->valueint;
    }

    if (cJSON_IsNumber(total) && total->valueint != -1) {
        pr.total = amount->valueint;
    }

    if (cJSON_IsNumber(orderId) && orderId->valueint != -1) {
        pr.orderId = orderId->valueint;
    }

    if (cJSON_IsNumber(status) && status->valueint != -1) {
        pr.status = status->valueint;
    }

    if (cJSON_IsNumber(total) && total->valueint != -1) {
        pr.total = total->valueint;
    }

    sr.time = deserialize_Time(time);
    return sr;

}

SellingRecord deserialize_SellingRecord(const cJSON *json) {
    SellingRecord sr;
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
        sr.id = id->valueint;
    }

    if (cJSON_IsNumber(partId) && partId->valueint != -1) {
        sr.partId = partId->valueint;
    }

    if (cJSON_IsNumber(status) && status->valueint != -1) {
        sr.status = status->valueint;
    }

    if (cJSON_IsNumber(guestId) && guestId->valueint != -1) {
        sr.guestId = guestId->valueint;
    }

    if (cJSON_IsNumber(amount) && amount->valueint != -1) {
        sr.amount = amount->valueint;
    }

    if (cJSON_IsNumber(total) && total->valueint != -1) {
        sr.total = total->valueint;
    }

    sr.time = deserialize_Time(time);

    if (cJSON_IsNumber(giftId) && giftId->valueint != -1) {
        sr.giftId = giftId->valueint;
    }
    if (cJSON_IsNumber(orderId) && orderId->valueint != -1) {
        sr.orderId = orderId->valueint;
    }

    return sr;
}