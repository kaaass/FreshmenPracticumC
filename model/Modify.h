//
// Created by Kevin on 2019/3/26.
//

#include "../data/DataManager.h"
#include "../data/TableOrder.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"
#include "../core/Database.h"
#include "../data/TableMountings.h"
#include "../util/Time.h"
#include "Insert.h"

#include <stdbool.h>
#include <assert.h>

#ifndef FRESHMAN_PROJ_C_TABLEMODIFY_H
#define FRESHMAN_PROJ_C_TABLEMODIFY_H

bool deletePurchaseRecord(PurchaseRecord *purchaseRecord);
bool deleteSellingRecord(SellingRecord *sellingRecord);
bool deleteOrder(Order *order);

bool modifyOrder(Order *order, const int *opId, int opCount, double price);

#endif //FRESHMAN_PROJ_C_TABLEMODIFY_H
