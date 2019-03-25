//
// Created by hasee on 2019/3/19.
//
#ifndef FRESHMAN_PROJ_C_TABLEORDER_H
#define FRESHMAN_PROJ_C_TABLEORDER_H

/**
 * 数据表：订单
 */
#define MAX_OP_ID 100

enum OrderStatus {
    ORDER_NORMAL = 0, ORDER_DELETED, ORDER_SALES_RETURN, ORDER_GIFT
};

enum OrderType {
    ORDER_PURCHASE = 0, ORDER_SINGLE_BUY, ORDER_WHOLE_SALE
};

#define DATA_TYPE_Order 7

typedef struct {
    int id;
    enum OrderType type;
    enum OrderStatus status;
    int opCount;
    int opId[MAX_OP_ID];
    double price;
} Order;

#endif //FRESHMAN_PROJ_C_TABLEORDER_H
