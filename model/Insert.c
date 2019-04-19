//
// Created by guyis on 2019/3/31.
//

#include <assert.h>
#include "Insert.h"
#include "../data/DataManager.h"
#include "../data/TableGuest.h"
#include "../data/TableProvider.h"
#include "../core/Config.h"
#include "../data/TableMountings.h"
#include "Gift.h"

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
 * @param change 是否改变库存
 */
void Insert_sellingRecord(SellingRecord *data, bool change) {
    assert(data);
    // 减少库存
    if (change) {
        Mountings *mounting = GetById(Mountings, MOUNTINGS, data->partId);
        mounting->amount -= data->amount;
    }
    Database_pushBack(SELLING_RECORD, Data(SellingRecord, data));
}

/**
 * 插入PurchaseRecord记录
 * @param data
 * @param change 是否改变库存
 */
void Insert_purchaseRecord(PurchaseRecord *data, bool change) {
    assert(data);
    // 增加库存
    if (change) {
        Mountings *mounting = GetById(Mountings, MOUNTINGS, data->partId);
        mounting->amount += data->amount;
    }
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
    // 进货时，账户余额不能是负的
    double accountBalance = Config_optDouble(LITERAL("accountBalance"), 5000000);
    if (orderType == ORDER_PURCHASE && totalPrice > accountBalance) {
        *info = STR_BUF("账户余额不能为负！");
        return false;
    }
    // 销售时，货品存量不能为负
    ForEach(cur, records) {
        RecordParam *data = GetData(RecordParam, cur);
        Mountings *mounting = GetById(Mountings, MOUNTINGS, data->partId);
        Provider *provider;
        if (data->amount > mounting->amount) {
            provider = GetById(Provider, PROVIDER, mounting->sellerId);
            *info = concat(3, LITERAL("商品 "), mounting->name
                    , LITERAL("（"), provider->name, LITERAL("）的库存不足！"));
            return false;
        }
    }
    return true;
}

/**
 * 订单添加逻辑
 * @param records
 * @param curGuest
 * @param orderType
 */
void Insert_appendOrderLogic(List *records, Guest curGuest, enum OrderType orderType) {
    int opId[MAX_OP_ID], opCnt = 0;
    double totalPrice = 0;
    int orderId;
    // 生成订单号
    orderId = Database_size(ORDER) + 1;
    // 物品操作
    ForEach(cur, records) {
        RecordParam *data = GetData(RecordParam, cur);
        totalPrice += data->total; // 计算总价
        // 添加记录
        if (orderType == ORDER_PURCHASE) { // 进货
            PurchaseRecord record = {
                    .partId = data->partId,
                    .sellerId = curGuest.id,
                    .amount = data->amount,
                    .total = data->total,
                    .price = data->price,
                    .orderId = orderId,
                    .status = PURCHASE_NORMAL,
                    .time = data->time
            };
            Insert_purchaseRecord(&record, true);
            opId[opCnt++] = Database_size(PURCHASE_RECORD);
        } else { // 销售
            SellingRecord record = {
                    .partId = data->partId,
                    .guestId = curGuest.id,
                    .amount = data->amount,
                    .total = data->total,
                    .price = data->price,
                    .orderId = orderId,
                    .status = SELLING_NORMAL,
                    .time = data->time
            };
            Insert_sellingRecord(&record, true);
            opId[opCnt++] = Database_size(SELLING_RECORD);
        }
    }
    // 送礼
    if (orderType != ORDER_PURCHASE) {
        if (insertGift(opId, opCnt)) {
            // 记录下礼品
            opId[opCnt++] = Database_size(SELLING_RECORD);
        }
    }
    // 插入订单
    Order order = {
            .type = orderType,
            .status = ORDER_NORMAL,
            .opCount = opCnt,
            .price = totalPrice
    };
    memcpy(order.opId, opId, opCnt * sizeof(int));
    Insert_order(&order);
    // 变更账户余额
    double accountBalance = Config_optDouble(LITERAL("accountBalance"), 5000000);
    accountBalance += (orderType == ORDER_PURCHASE ? -1: 1) * totalPrice;
    Config_setDouble(LITERAL("accountBalance"), accountBalance);
}