//
// Created by guyis on 2019/3/19.
//
#include "../core/Database.h"
#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_DATAMANAGER_H
#define FRESHMAN_PROJ_C_DATAMANAGER_H

extern Database *CONFIG;
extern Database *GUEST;
extern Database *SELLING_RECORD;
extern Database *ORDER;
extern Database *PROVIDER;
extern Database *MOUNTINGS;
extern Database *PURCHASE_RECORD;

void DataManager_init();
void DataManager_finalize();
void DataManager_save(string dir);
void DataManager_load(string dir);

#endif //FRESHMAN_PROJ_C_DATAMANAGER_H
