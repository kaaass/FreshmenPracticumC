//
// Created by hasee on 2019/3/19.
//
#include "../util/StringUtil.h"


#ifndef FRESHMAN_PROJ_C_TABLEPROVIDER_H
#define FRESHMAN_PROJ_C_TABLEPROVIDER_H

/**
 * 数据表：供应商
 */
const int DATA_TYPE_Provider = 6;

typedef struct {
    int id;
    stringbuf name;
    stringbuf phone;
} Provider;

#endif //FRESHMAN_PROJ_C_TABLEPROVIDER_H
