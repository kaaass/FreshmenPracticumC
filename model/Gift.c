//
// Created by Kevin on 2019/4/16.
//

#include "Gift.h"
#include "../core/Config.h"

/**
 * 通过销售记录获取赠送礼品的MountingId
 * @param sellingRecord 销售记录id
 * @param sellingRecordCount 销售记录数量
 * @return 要赠送的gift对应的MountingsId
 */
int getGift(int sellingRecordIds[], int sellingRecordCount) {

    //计算销售总价
    double tot = 0;
    for (int i = 0; i < sellingRecordCount; ++i) {
        SellingRecord *cur = GetById(SellingRecord, SELLING_RECORD, sellingRecordIds[i]);

        //sellingRecord有误
        if(cur == NULL || cur->status == SELLING_DELETED)
            return -1;
        tot += cur->total;
    }

    //送礼门槛
    int bound1 = 0, bound2 = 0;

    //获取能做gift的Mountigs的id
    int* gifts = NULL;
    int giftsCount[] = {0};

    ForEach(cur, CONFIG) {

        Config *config = GetData(Config, cur);

        if(EQUAL(config->key, LITERAL("giftId"))) {
            gifts = Config_getIntArray(STR_BUF("giftId"), giftsCount);
        } else if(EQUAL(config->key, LITERAL("giftSendingBound1"))) {
            bound1 = Config_optInteger(STR_BUF("giftSendingBound1"), -1);
        } else if(EQUAL(config->key, LITERAL("giftSendingBound2"))) {
            bound2 = Config_optInteger(STR_BUF("giftSendingBound2"), -1);
        }
    }

    //无合适礼品可送
    if(*giftsCount == 0 || gifts == NULL)
        return -2;
    //无合适礼品可送
    else if(tot < bound1)
        return -3;

    //获取库存最多的礼物
    int highId = 0;
    double highAmount = 0;

    for (int i = 0; i < *giftsCount; ++i) {
        Mountings* mountings = GetById(Mountings, MOUNTINGS, gifts[i]);
        if(tot <= bound2) {
            if(mountings->price <= 100 && mountings->amount > highAmount) {
                highAmount = mountings->amount;
                highId = gifts[i];
            }
        } else {
            if(mountings->price > 100 && mountings->amount > highAmount) {
                highAmount = mountings->amount;
                highId = gifts[i];
            }
        }
    }
    if(highAmount == 0)
        return -2;
    else
        return highId;
}

bool insertGift(int sellingRecordIds[], int sellingRecordCount) {
    int mountingsId = getGift(sellingRecordIds, sellingRecordCount);

    //sellingRecord有误
    if(mountingsId == -1)
        return false;

    //无合适礼品可送
    if(mountingsId == -2)
        return false;

    //价格太低不送礼品
    if(mountingsId == -3)
        return false;

    //插入新礼品
    Mountings *mountings = GetById(Mountings, MOUNTINGS, mountingsId);
    SellingRecord newSellingRecord = {
            .partId = mountingsId,
            .status = SELLING_GIFT,
            .amount = 1,
            .price = mountings->price,
            .time = Time_getNow(),
            .orderId = GetById(SellingRecord, SELLING_RECORD, sellingRecordIds[0])->orderId
    };
    Insert_sellingRecord(&newSellingRecord, true);
    mountings->amount--;
    return true;
}