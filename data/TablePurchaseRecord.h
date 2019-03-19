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
const int DATA_TYPE_Test = 3;
enum PurchaseRecordStatus {
    status_ormal = 0, status_deleted = 1, status_salesReturn = 2
};

typedef struct {
    int id;
    int partId;
    int sellerId;
    int amount;
    float total;
    int orderId
    PurchaseRecordStatus status;
    Time time;
} Mountings;

#endif //FRESHMAN_PROJ_C_TABLEPURCHASERECORD_H
