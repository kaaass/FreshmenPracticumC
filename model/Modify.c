//
// Created by Kevin on 2019/3/26.
//
#include "Modify.h"

bool deletePurchaseRecord(int purchaseRecordId, stringbuf *reason) {
    PurchaseRecord *purchaseRecord = GetById(PurchaseRecord ,PURCHASE_RECORD, purchaseRecordId);
    if(purchaseRecord == NULL) {
        *reason = STR_BUF("进货记录不存在！");
        return false;
    }
    purchaseRecord->status = PURCHASE_DELETED;
    Mountings *mountings = NULL;
    mountings = GetById(Mountings, MOUNTINGS, purchaseRecord->partId);
    if(mountings == NULL) return false;
    if(mountings->amount < purchaseRecord->amount) {
        *reason = STR_BUF("配件库存不足，无法退账！");
        return false;
    }
    mountings->amount -= purchaseRecord->amount;
    return true;
}

bool deleteSellingRecord(int sellingRecordId, stringbuf *reason) {
    SellingRecord *sellingRecord = GetById(SellingRecord, SELLING_RECORD, sellingRecordId);
    if(sellingRecord == NULL) return false;

    //check
    double accountBalance = Config_optDouble(LITERAL("accountBalance"), -1);
    if(accountBalance > 0 && accountBalance < sellingRecord->total){
        *reason = STR_BUF("运行资本不足，退账失败！");
        return false;
    }

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
            if(!deletePurchaseRecord(order->opId[i], NULL)) return false;
        }
    } else if (type == ORDER_SINGLE_BUY || type == ORDER_WHOLE_SALE) {
        for (int i = 0; i < order->opCount; ++i) {
            if(!deleteSellingRecord(order->opId[i], NULL)) return false;
        }
    }
    else
        return false;

    return true;
}

bool modifyOrderOfSellingRecord(int orderId, int sellingRecordId, SellingRecord *newSellingRecord, stringbuf *reason) {
    // TODO: 增加错误原因
    Order *order = GetById(Order, ORDER, orderId);
    SellingRecord *sellingRecord = GetById(SellingRecord, SELLING_RECORD, sellingRecordId);
    if(order == NULL) {
        *reason = STR_BUF("订单不存在！");
        return false;
    }
    if (sellingRecord == NULL){
        *reason = STR_BUF("销售记录不存在！");
        return false;
    }

    if (newSellingRecord == NULL) return false;
    if(!deleteSellingRecord(sellingRecordId, NULL)) {
        *reason = STR_BUF("原销售记录删除失败!");
        return false;
    }

    order->status = ORDER_DELETED;
    Order newOrder = {.status = ORDER_SALES_RETURN, .type = order->type};
    SellingRecord *newSellingRecord2 = GetById(SellingRecord, SELLING_RECORD, Database_size(SELLING_RECORD));
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        newOrder.opId[count++] = order->opId[i];

    }

    newOrder.opId[count++] = newSellingRecord2->id;
    newOrder.opCount = count;
    Insert_order(&newOrder);

    int newOrderId = Database_size(ORDER);
    newSellingRecord->orderId = newOrderId;
    Insert_sellingRecord(newSellingRecord, false);

    return true;
}

bool modifyOrderOfPurchaseRecord(int orderId, int purchaseRecordId, PurchaseRecord *newPuachaseRecord, stringbuf *reason) {
    // TODO: 增加错误原因
    Order *order = GetById(Order, ORDER, orderId);
    PurchaseRecord *purchaseRecord = GetById(PurchaseRecord, PURCHASE_RECORD, purchaseRecordId);
    if(order == NULL) {
        *reason = STR_BUF("订单不存在！");
        return false;
    }
    if(purchaseRecord == NULL) {
        *reason = STR_BUF("销售记录不存在！");
        return false;
    }

    if(newPuachaseRecord == NULL) return false;

    if(!deletePurchaseRecord(purchaseRecordId, NULL)) {
        *reason = STR_BUF("原进货记录删除失败");
        return false;
    }

    order->status = ORDER_DELETED;
    Order newOrder = {.status = ORDER_SALES_RETURN, .type = order->type};
    PurchaseRecord *newPuachaseRecord2 = GetById(PurchaseRecord, PURCHASE_RECORD, Database_size(PURCHASE_RECORD));
    int count = 0;
    for (int i = 0; i < order->opCount; ++i) {
        newOrder.opId[count++] = order->opId[i];
    }
    newOrder.opId[count++] = newPuachaseRecord2->id;
    newOrder.opCount = count;

    Insert_order(&newOrder);
    int newOrderId = Database_size(ORDER);
    newPuachaseRecord->orderId = newOrderId;
    Insert_purchaseRecord(newPuachaseRecord, false);

    return true;
}

bool modifyMountingsPrice(int mountingsId, double price) {
    Mountings *mountings = GetById(Mountings, MOUNTINGS, mountingsId);
    if(mountings == NULL) return false;
    mountings->price = price;
    return true;
}
