//
// Created by St on 2019-03-19.
//
#include "../util/Time.h"

#ifndef FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
#define FRESHMAN_PROJ_C_TABLESELLINGRECORD_H

/**
 * 数据表：销售记录
 */
#define DATA_TYPE_SellingRecord 5

enum SellingRecordStatus {
    SELLING_NORMAL = 0, SELLING_DELETED, SELLING_SALES_RETURN, SELLING_GIFT
};

typedef struct {
    int id;
    int partId;
    enum SellingRecordStatus status;
    int guestId;
    int amount;
    double total;
    Time time;
    int orderId;
} SellingRecord;

#endif //FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
