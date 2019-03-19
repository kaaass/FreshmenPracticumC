//
// Created by guyis on 2019/3/19.
//

#include "../data/TableConfig.h"
#include "DataManager.h"
#include"TableOrder.h"
#include"TableProvider.h"
#include "TableMountings.h"
#include "TablePurchaseRecord.h"

void DataManager_init() {
    CONFIG = Create(Config);
    GUEST = Create(Guest);
    SELLING_RECORD = Create(SellingRecord);

    ORDER  = Create(Order);
    PROVIDER = Create(Provider);
    MOUNTINGS = Create(Mountings);
    PURCHASE_RECORD = Create(PurchaseRecord);
}