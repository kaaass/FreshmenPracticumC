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

    Order newOrder = {
            .type = order->type,
            .status = ORDER_SALES_RETURN,
    };
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        if(order->opId[i] != sellingRecordId)
            newOrder.opId[count++] = order->opId[i];
        else
            newOrder.opId[count++] = newSellingRecord->id;
    }
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

    Order newOrder = {
            .type = order->type,
            .status = ORDER_SALES_RETURN,
    };
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        if(order->opId[i] != purchaseRecordId)
            newOrder.opId[count++] = order->opId[i];
        else
            newOrder.opId[count++] = newPuachaseRecord->id;
    }
    newOrder.opCount = count;
    if(!deleteOrder(orderId)) return false;
    if(!deletePurchaseRecord(purchaseRecordId)) return false;
    Insert_order(&newOrder);
    return true;
}
