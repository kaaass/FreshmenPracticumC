//
// Created by St on 2019-03-19.
//

#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
#define FRESHMAN_PROJ_C_TABLESELLINGRECORD_H

/**
 * 数据表：销售记录
 */
const int DATA_TYPE_SellingRecord = 5;

enum SellingRecordStatus {
    normal = 0, del, salesReturn, gift
};

typedef struct {
    int id;
    int partId;
    enum SellingRecordStatus status;
    int guestId;
    int amount;
    float total;
    Time time;
    int giftId;
    int orderId;
} SellingRecord;

#endif //FRESHMAN_PROJ_C_TABLESELLINGRECORD_H
