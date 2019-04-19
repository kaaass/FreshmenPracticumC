//
// Created by guyis on 2019/3/31.
//
#include "../util/StringUtil.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"
#include "../data/TableOrder.h"
#include "../core/Database.h"
#include "../data/TableGuest.h"

#ifndef FRESHMAN_PROJ_C_INSERT_H
#define FRESHMAN_PROJ_C_INSERT_H

#define DATA_TYPE_RecordParam 15 | ID_LIKE

typedef struct {
    int id;
    int partId;
    int amount;
    double price;
    double total;
    Time time;
} RecordParam;

int Insert_hasGuest(string name, string phone);

void Insert_guest(string name, string phone);

int Insert_hasProvider(string name, string phone);

void Insert_provider(string name, string phone);

void Insert_sellingRecord(SellingRecord *data, bool change);

void Insert_purchaseRecord(PurchaseRecord *data, bool change);

void Insert_order(Order *);

bool Insert_checkForAppend(List *records, Guest curGuest, enum OrderType orderType, float totalPrice, stringbuf *info);

void Insert_appendOrderLogic(List *records, Guest curGuest, enum OrderType orderType);

#endif //FRESHMAN_PROJ_C_INSERT_H
