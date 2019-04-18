//
// Created by guyis on 2019/3/31.
//

#include <assert.h>
#include "Insert.h"
#include "../data/DataManager.h"
#include "../data/TableGuest.h"
#include "../data/TableProvider.h"

/**
 * 是否存在Guest记录
 * @param name
 * @param phone
 * @return
 */
int Insert_hasGuest(string name, string phone) {
    bool matchName = empty(name),
            matchPhone = empty(phone);
    assert(!(matchName && matchPhone));
    ForEach(cur, GUEST) {
        Guest *data = GetData(Guest, cur);
        if ((matchName || EQUAL(name, data->name)) &&
            (matchPhone || EQUAL(phone, data->phone))) {
            return data->id;
        }
    }
    return 0;
}

/**
 * 插入Guest记录
 * @param name
 * @param phone
 */
void Insert_guest(string name, string phone) {
    assert(!empty(name));
    assert(!empty(phone));
    Guest data = {.name = name, .phone = phone};
    Database_pushBack(GUEST, Data(Guest, &data));
}

/**
 * 是否存在Provider记录
 * @param name
 * @param phone
 * @return
 */
int Insert_hasProvider(string name, string phone) {
    bool matchName = empty(name),
            matchPhone = empty(phone);
    ForEach(cur, PROVIDER) {
        Provider *data = GetData(Provider, cur);
        if ((matchName || EQUAL(name, data->name)) &&
            (matchPhone || EQUAL(phone, data->phone))) {
            return data->id;
        }
    }
    return 0;
}

/**
 * 插入Provider记录
 * @param name
 * @param phone
 */
void Insert_provider(string name, string phone) {
    assert(!empty(name));
    assert(!empty(phone));
    Provider data = {.name = name, .phone = phone};
    Database_pushBack(PROVIDER, Data(Provider, &data));
}

/**
 * 插入SellingRecord记录
 * @param data
 */
void Insert_sellingRecord(SellingRecord *data) {
    assert(data);
    Database_pushBack(SELLING_RECORD, Data(SellingRecord, data));
}

/**
 * 插入PurchaseRecord记录
 * @param data
 */
void Insert_purchaseRecord(PurchaseRecord *data) {
    assert(data);
    Database_pushBack(PURCHASE_RECORD, Data(PurchaseRecord, data));
}

/**
 * 插入Order记录
 * @param data
 */
void Insert_order(Order *data) {
    assert(data);
    Database_pushBack(ORDER, Data(Order, data));
}

/**
 * 订单添加的正确性检查
 * @param records
 * @param curGuest
 * @param orderType
 * @param totalPrice
 * @param info
 * @return
 */
bool Insert_checkForAppend(List *records, Guest curGuest, enum OrderType orderType, float totalPrice, stringbuf *info) {
    return true;
}

/**
 * 订单添加逻辑
 * @param records
 * @param curGuest
 * @param orderType
 */
void Insert_appendOrderLogic(List *records, Guest curGuest, enum OrderType orderType) {
    // TODO: 若进货需要更新mountings的价格，增礼逻辑
}