//
// Created by guyis on 2019/3/23.
//
#include "../util/StringUtil.h"
#include "../util/Time.h"
#include "../data/TableGuest.h"
#include "../data/TableProvider.h"
#include "../data/TableConfig.h"
#include "../data/TableMountings.h"
#include "../data/TableOrder.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"
#include "cJSON.h"

#ifndef FRESHMAN_PROJ_C_SERIALIZER_H
#define FRESHMAN_PROJ_C_SERIALIZER_H

#define Serialize(type,data) serialize_##type(data)
#define Deserialize(type,data) deserialize_##type(data)

/*
 * 序列化方法
 */
cJSON *serialize_Time(Time);
cJSON *serialize_Guest(Guest);
cJSON *serialize_Provider(Provider);
cJSON *serialize_Config(Config);
cJSON *serialize_Mountings(Mountings);
cJSON *serialize_Order(Order);
cJSON *serialize_PurchaseRecord(PurchaseRecord);
cJSON *serialize_SellingRecord(SellingRecord);


/*
 * 反序列化方法
 */
Time deserialize_Time(const cJSON *);
Guest deserialize_Guest(const cJSON *);
Provider deserialize_Provider(const cJSON *);
Config deserialize_Config(const cJSON *);
Mountings deserialize_Mountings(const cJSON *);
Order deserialize_Order(const cJSON *);
PurchaseRecord deserialize_PurchaseRecord(const cJSON *);
SellingRecord deserialize_SellingRecord(const cJSON *);


#endif //FRESHMAN_PROJ_C_SERIALIZER_H
