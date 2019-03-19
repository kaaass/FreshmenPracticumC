//
// Created by guyis on 2019/3/19.
//

#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_TABLECONFIG_H
#define FRESHMAN_PROJ_C_TABLECONFIG_H

/**
 * 数据表：
 */
const int DATA_TYPE_Config = 8;

typedef struct {
    int id;
    stringbuf key;
    stringbuf value;
} Config;

#endif //FRESHMAN_PROJ_C_TABLECONFIG_H
