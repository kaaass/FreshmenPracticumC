//
// Created by St on 2019-03-19.
//

#ifndef FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
#define FRESHMAN_PROJ_C_TABLESELLINGRECORD_H

#include "../util/StringUtil.h"

const int DATA_TYPE_Test = 4;

enum {
    Normal = 0 ,Del ,SalesReturn, Gift
}Condition;

typedef struct {
    int id;
    int partid;
    Condition status;
    int guestid;
    int amount;
    float total;
    Time time;
    int giftid;
    int orderid;
} SellingRecord;


#endif //FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
