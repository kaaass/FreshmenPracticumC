//
// Created by Kevin on 2019/3/26.
//
#include "Modify.h"


//通过PurchaseRecord指针删除单个进货记录
bool deletePurchaseRecord(PurchaseRecord *purchaseRecord) {
    if(purchaseRecord == NULL) return false;
    purchaseRecord->status = PURCHASE_DELETED;
    Mountings *mountings = NULL;
    mountings = GetById(Mountings, MOUNTINGS, purchaseRecord->partId);
    if(mountings == NULL) return false;
    if(mountings->amount < purchaseRecord->amount) return false;
    mountings->amount -= purchaseRecord->amount;
    return true;
}


//通过SellingRecord指针删除单个销售记录
bool deleteSellingRecord(SellingRecord *sellingRecord) {
    if(sellingRecord == NULL) return false;
    sellingRecord->status = SELLING_DELETED;
    Mountings *mountings = NULL;
    mountings = GetById(Mountings, MOUNTINGS, sellingRecord->partId);
    if(mountings == NULL) return false;
    mountings->amount += sellingRecord->amount;
    return true;
}


//通过订单指针删除单个订单
bool deleteOrder(Order *order) {
    if(order == NULL) return false;
    order->status = ORDER_DELETED;
    int type = order->type;

    if (type == ORDER_PURCHASE) {
        PurchaseRecord *purchaseRecord = NULL;
        for (int i = 0; i < order->opCount; ++i) {
            purchaseRecord = GetById(PurchaseRecord, PURCHASE_RECORD, order->opId[i]);
            if(purchaseRecord == NULL) return false;
            if(!deletePurchaseRecord(purchaseRecord)) return false;
        }
    } else if (type == ORDER_SINGLE_BUY || type == ORDER_WHOLE_SALE) {
        SellingRecord *sellingRecord = NULL;
        for (int i = 0; i < order->opCount; ++i) {
            sellingRecord = GetById(SellingRecord, SELLING_RECORD, order->opId[i]);
            if(sellingRecord == NULL) return false;
            if(!deleteSellingRecord(sellingRecord)) return false;
        }
    }
    else
        return false;

    return true;
}

//通过订单数组，修改订单的进货/销售记录
bool modifyOrder(Order *order, const int *opId, int opCount, double price) {
    if(order == NULL) return false;
    Order newOrder = {
            .type = order->type,
            .status = ORDER_SALES_RETURN,
            .opCount = opCount,
            .price = price
    };

    if(!deleteOrder(order)) return false;
    for (int i = 0; i < opCount; ++i) {
        newOrder.opId[i] = opId[i];
    }
    Insert_order(order);
    return true;
}
