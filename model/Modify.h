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
#include "../core/Config.h"

#include <stdbool.h>
#include <assert.h>

#ifndef FRESHMAN_PROJ_C_TABLEMODIFY_H
#define FRESHMAN_PROJ_C_TABLEMODIFY_H

bool deletePurchaseRecord(int purchaseRecordId, stringbuf *reason);

bool deleteSellingRecord(int sellingRecordId, stringbuf *reason);
bool deleteOrder(int orderId);

bool modifyOrderOfSellingRecord(int orderId, int sellingRecordId, SellingRecord *newSellingRecord, stringbuf *reason);

bool
modifyOrderOfPurchaseRecord(int orderId, int purchaseRecordId, PurchaseRecord *newPuachaseRecord, stringbuf *reason);

bool modifyMountingsPrice(int mountingsId, double price);
#endif //FRESHMAN_PROJ_C_TABLEMODIFY_H
