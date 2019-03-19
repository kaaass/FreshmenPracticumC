//
// Created by guyis on 2019/3/19.
//

#include "../data/TableConfig.h"
#include "DataManager.h"

void DataManager_init() {
    CONFIG = Create(Config);
    GUEST = Create(Guest);
    SELLING_RECORD = Create(SellingRecord);

}