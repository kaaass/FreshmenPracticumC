//
// Created by Kevin on 2019/3/19.
//
#include "../util/StringUtil.h"
#include "../util/Time.h"


#ifndef FRESHMAN_PROJ_C_TABLEPURCHASERECORD_H
#define FRESHMAN_PROJ_C_TABLEPURCHASERECORD_H

/**
 * 数据表：进货记录
 */
#define DATA_TYPE_PurchaseRecord 3

enum PurchaseRecordStatus {
    normal = 0, deleted = 1, salesReturn = 2
};

typedef struct {
    int id;
    int partId;
    int sellerId;
    int amount;
    float total;
    int orderId
    enum PurchaseRecordStatus status;
    Time time;
} PurchaseRecord;

#endif //FRESHMAN_PROJ_C_TABLEPURCHASERECORD_H