//
// Created by Kevin on 2019/3/19.
//
#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_TABLEMOUNTINGS_H
#define FRESHMAN_PROJ_C_TABLEMOUNTINGS_H

/**
 * 数据表：零配件
 */
#define DATA_TYPE_Mountings 2

enum MountingsType {
    MOUNTINGS_MOUSE = 0,
    MOUNTINGS_KEYBOARD = 1,
    MOUNTINGS_MEMORY = 2,
    MOUNTINGS_GRAPHICS_CARD = 3,
    MOUNTINGS_HARD_DISK = 4,
    MOUNTINGS_CPU = 5,
    MOUNTINGS_SCREEN = 6
};

typedef struct {
    int id;
    enum MountingsType type;
    int sellerId;
    stringbuf name;
    int amount;
    int giftPriority;
    double price;
} Mountings;

#endif //FRESHMAN_PROJ_C_TABLEMOUNTINGS_H
