//
// Created by guyis on 2019/3/19.
//

#include "../data/TableConfig.h"
#include "DataManager.h"
#include"TableOrder.h"
#include"TableProvider.h"

void DataManager_init() {
    CONFIG = Create(Config);
    ORDER  = Create(Order);
    PROVIDER = Create(Provider);
}