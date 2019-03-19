//
// Created by Kevin on 2019/3/19.
//
#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_TABLEMOUNTINGS_H
#define FRESHMAN_PROJ_C_TABLEMOUNTINGS_H

/**
 * 数据表：零配件
 */
const int DATA_TYPE_Mountings = 2;
enum MountingsType {
    type_mouse = 0, type_keyboard = 1, type_memory = 2, type_graphicsCard = 3, type_hardDisk = 4
};

typedef struct {
    int id;
    MountingsType type;
    int sellerId;
    stringbuf name;
    int amount;
    int giftPriority;
    double price
} Mountings;

#endif //FRESHMAN_PROJ_C_TABLEMOUNTINGS_H
