//
// Created by guyis on 2019/3/23.
//
#include "../util/StringUtil.h"
#include "../util/Time.h"
#include "cJSON.h"

#ifndef FRESHMAN_PROJ_C_SERIALIZER_H
#define FRESHMAN_PROJ_C_SERIALIZER_H

#define Serialize(type,data) serialize_##type(data)
#define Deserialize(type,data) deserialize_##type(data)

/*
 * 序列化方法
 */
cJSON *serialize_Time(Time);

/*
 * 反序列化方法
 */
Time deserialize_Time(const cJSON *);

#endif //FRESHMAN_PROJ_C_SERIALIZER_H
