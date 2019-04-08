//
// Created by guyis on 2019/3/31.
//
#include "../util/StringUtil.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"
#include "../data/TableOrder.h"

#ifndef FRESHMAN_PROJ_C_INSERT_H
#define FRESHMAN_PROJ_C_INSERT_H

bool Insert_hasGuest(string name, string phone);
void Insert_guest(string name, string phone);
bool Insert_hasProvider(string name, string phone);
void Insert_provider(string name, string phone);
void Insert_sellingRecord(SellingRecord *);
void Insert_purchaseRecord(PurchaseRecord *);
void Insert_order(Order *);

#endif //FRESHMAN_PROJ_C_INSERT_H
