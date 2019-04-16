//
// Created by Kevin on 2019/4/16.
//
#include "../data/DataManager.h"
#include "../core/Database.h"
#include "../data/TableMountings.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"

#ifndef FRESHMAN_PROJ_C_FORECASE_H
#define FRESHMAN_PROJ_C_FORECASE_H

double forecasePurchasePrice(double time, int mountingsId);
double forecaseSellingPrice(double time, int mountingsId);

#endif //FRESHMAN_PROJ_C_FORECASE_H
