//
// Created by hasee on 2019/3/19.
//
#include "../util/StringUtil.h"


#ifndef FRESHMAN_PROJ_C_TABLEORDER_H
#define FRESHMAN_PROJ_C_TABLEORDER_H

/**
 * 数据表：订单
 */
#define MAX_OP_ID 100;

enum OrderStatus {
    normal = 0, del, salesReturn, gift
};

enum OrderType {
    purchase = 0, singleBuy, wholeSale
};

#define DATA_TYPE_Order 7

typedef struct {
    int id;
    enum OrderType type;
    enum OrderStatus status;
    int opCount;
    int opId[MAX_OP_ID];
    float price;
} Order;

#endif //FRESHMAN_PROJ_C_TABLEORDER_H
