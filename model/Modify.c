//
// Created by Kevin on 2019/3/26.
//
#include "Modify.h"

bool deletePurchaseRecord(int purchaseRecordId) {
    PurchaseRecord *purchaseRecord = GetById(PurchaseRecord ,PURCHASE_RECORD, purchaseRecordId);
    if(purchaseRecord == NULL) return false;
    purchaseRecord->status = PURCHASE_DELETED;
    Mountings *mountings = NULL;
    mountings = GetById(Mountings, MOUNTINGS, purchaseRecord->partId);
    if(mountings == NULL) return false;
    if(mountings->amount < purchaseRecord->amount) return false;
    mountings->amount -= purchaseRecord->amount;
    return true;
}

bool deleteSellingRecord(int sellingRecordId) {
    SellingRecord *sellingRecord = GetById(SellingRecord, SELLING_RECORD, sellingRecordId);
    if(sellingRecord == NULL) return false;

    //check
    double accountBalance = Config_optDouble(LITERAL("accountBalance"), -1);
    if(accountBalance > 0 && accountBalance < sellingRecord->total)
        return false;

    sellingRecord->status = SELLING_DELETED;
    Mountings *mountings = NULL;
    mountings = GetById(Mountings, MOUNTINGS, sellingRecord->partId);
    if(mountings == NULL) return false;
    mountings->amount += sellingRecord->amount;
    return true;
}

bool deleteOrder(int orderId) {
    Order *order = GetById(Order, ORDER, orderId);
    if(order == NULL) return false;
    order->status = ORDER_DELETED;
    int type = order->type;

    if (type == ORDER_PURCHASE) {
        for (int i = 0; i < order->opCount; ++i) {
            if(!deletePurchaseRecord(order->opId[i])) return false;
        }
    } else if (type == ORDER_SINGLE_BUY || type == ORDER_WHOLE_SALE) {
        for (int i = 0; i < order->opCount; ++i) {
            if(!deleteSellingRecord(order->opId[i])) return false;
        }
    }
    else
        return false;

    return true;
}

bool modifyOrderOfSellingRecord(int orderId, int sellingRecordId, SellingRecord *newSellingRecord) {
    Order *order = GetById(Order, ORDER, orderId);
    SellingRecord *sellingRecord = GetById(SellingRecord, SELLING_RECORD, sellingRecordId);
    if(order == NULL) return false;
    if(sellingRecord == NULL) return false;
    if(newSellingRecord == NULL) return false;
    Insert_sellingRecord(newSellingRecord, false);
    Order newOrder = {.status = ORDER_SALES_RETURN, .type = order->type};
    SellingRecord *newSellingRecord2 = GetById(SellingRecord, SELLING_RECORD, Database_size(SELLING_RECORD));
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        newOrder.opId[count++] = order->opId[i];

    }

    newOrder.opId[count++] = newSellingRecord2->id;
    newOrder.opCount = count;
    if(!deleteOrder(orderId)) return false;
    if(!deleteSellingRecord(sellingRecordId)) return false;
    Insert_order(&newOrder);
    return true;
}

bool modifyOrderOfPurchaseRecord(int orderId, int purchaseRecordId, PurchaseRecord *newPuachaseRecord){
    Order *order = GetById(Order, ORDER, orderId);
    PurchaseRecord *purchaseRecord = GetById(PurchaseRecord, PURCHASE_RECORD, purchaseRecordId);
    if(order == NULL) return false;
    if(purchaseRecord == NULL) return false;
    if(newPuachaseRecord == NULL) return false;
    Insert_purchaseRecord(newPuachaseRecord, false);
    Order newOrder = {.status = ORDER_SALES_RETURN, .type = order->type};
    PurchaseRecord *newPuachaseRecord2 = GetById(PurchaseRecord, PURCHASE_RECORD, Database_size(PURCHASE_RECORD));
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        newOrder.opId[count++] = order->opId[i];
    }
    newOrder.opId[count++] = newPuachaseRecord2->id;
    newOrder.opCount = count;
    if(!deleteOrder(orderId)) return false;
    if(!deletePurchaseRecord(purchaseRecordId)) return false;
    Insert_order(&newOrder);
    return true;
}

bool modifyMountingsPrice(int mountingsId, double price) {
    Mountings *mountings = GetById(Mountings, MOUNTINGS, mountingsId);
    if(mountings == NULL) return false;
    mountings->price = price;
    return true;
}
