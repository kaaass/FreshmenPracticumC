//
// Created by Kevin on 2019/4/16.
//

#ifndef FRESHMAN_PROJ_C_GIFTSELECTION_H
#define FRESHMAN_PROJ_C_GIFT_H

#include "../data/TableSellingRecord.h"
#include "../data/TableMountings.h"
#include "../core/Database.h"
#include "../data/DataManager.h"
#include "../model/Insert.h"
#include "../data/TableConfig.h"
#include "../util/StringUtil.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int getGift(int sellingRecordIds[], int sellingRecordCount);
bool insertGift(int sellingRecordIds[], int sellingRecordCount);

#endif //FRESHMAN_PROJ_C_GIFTSELECTION_H
