//
// Created by guyis on 2019/3/19.
//
#include "../core/Database.h"

#ifndef FRESHMAN_PROJ_C_DATAMANAGER_H
#define FRESHMAN_PROJ_C_DATAMANAGER_H

#include "TableGuest.h"
#include "TableSellingRecord.h"
Database *CONFIG ;
Database *GUEST;
Database *SELLING_RECORD;
Database *CONFIG;
Database *MOUNTINGS;
Database *PURCHASE_RECORD;

void DataManager_init();

#endif //FRESHMAN_PROJ_C_DATAMANAGER_H
