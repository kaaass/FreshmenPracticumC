//
// Created by St on 2019-03-26.
//

#include "Consultation.h"
#include "../data/TablePurchaseRecord.h"
#include "../data/TableMountings.h"
#include "../data/TableSellingRecord.h"
#include "../data/DataManager.h"
#include <stdbool.h>

//查询某种配件的进货/销售信息

int comparePurchaseRecord(const void *a, const void *b) {
    if (((PurchaseRecord *) a)->time.timeStamp < ((PurchaseRecord *) b)->time.timeStamp) return -1;
    if (((PurchaseRecord *) a)->time.timeStamp == ((PurchaseRecord *) b)->time.timeStamp) return 0;
    if (((PurchaseRecord *) a)->time.timeStamp > ((PurchaseRecord *) b)->time.timeStamp) return 1;
}

int compareSellingRecord(const void *a, const void *b) {
    if (((SellingRecord *) a)->time.timeStamp < ((SellingRecord *) b)->time.timeStamp) return -1;
    if (((SellingRecord *) a)->time.timeStamp == ((SellingRecord *) b)->time.timeStamp) return 0;
    if (((SellingRecord *) a)->time.timeStamp > ((SellingRecord *) b)->time.timeStamp) return 1;
}


Database *AccessoryIn(int type) {
    PurchaseRecord *accessoryin[1000];
    int num = 0;
    Mountings *trans;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        trans = GetById(Mountings, MOUNTINGS, record->partId);
        if (trans->type == type) {
            accessoryin[num] = record;
            num++;
        }
    }
    qsort(accessoryin, num, sizeof(PurchaseRecord *), comparePurchaseRecord);
    Database *point = arrayToDatabase(Data(PurchaseRecord, accessoryin), num);
    return point;
}

Database *AccessoryOut(int type) {
    SellingRecord *accessoryout[1000];
    int num = 0;
    Mountings *trans;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        trans = GetById(Mountings, MOUNTINGS, record->partId);
        if (trans->type == type) {
            accessoryout[num] = record;
            num++;
        }
    }
    qsort(accessoryout, num, sizeof(SellingRecord *), compareSellingRecord);
    Database *point = arrayToDatabase(Data(SellingRecord, accessoryout), num);
    return point;
}

//查询某个供货商的历史进货信息

Database *Supplier(int sellerId) {
    PurchaseRecord *supplier[1000];
    int num = 0;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        if (record->sellerId == sellerId) {
            supplier[num] = record;
            num++;
        }
    }
    qsort(supplier, num, sizeof(PurchaseRecord *), comparePurchaseRecord);
    Database *point = arrayToDatabase(Data(PurchaseRecord, supplier), num);
    return point;
}

//查询某个客户的历史采购信息

Database *Client(int guestId) {
    SellingRecord *guest[1000];
    int num = 0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        if (record->guestId == guestId) {
            guest[num] = record;
            num++;
        }
    }
    qsort(guest, num, sizeof(SellingRecord *), compareSellingRecord);
    Database *point = arrayToDatabase(Data(SellingRecord, guest), num);
    return point;
}