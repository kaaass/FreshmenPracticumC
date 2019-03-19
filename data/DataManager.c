//
// Created by guyis on 2019/3/19.
//

#include "../data/TableConfig.h"
#include "DataManager.h"
#include "TableMountings.h"
#include "TablePurchaseRecord.h"

void DataManager_init() {
    CONFIG = Create(Config);
    MOUNTINGS = Create(Mountings);
    PURCHASE_RECORD = Create(PurchaseRecord);
}