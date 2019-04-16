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
    int gifts[10];
    int giftsCount = 0;

    ForEach(cur, CONFIG) {

        Config *config = GetData(Config, cur);

        if(compareString(config->key, LITERAL("giftId")) == STRING_EQUAL) {

            int giftId = Config_optInteger(STR_BUF("giftId"), -1);
            gifts[giftsCount++] = giftId;

        } else if(compareString(config->key, LITERAL("giftSendingBound1")) == STRING_EQUAL) {
            bound1 = Config_optInteger(STR_BUF("giftSendingBound1"), -1);
        } else if(compareString(config->key, LITERAL("giftSendingBound2")) == STRING_EQUAL) {
            bound2 = Config_optInteger(STR_BUF("giftSendingBound2"), -1);
        }
    }

    //无合适礼品可送
    if(giftsCount == 0)
        return -2;
    //无合适礼品可送
    else if(tot < bound1)
        return -3;

    //获取库存最少的礼物
    int lowId = 0;
    double lowAmount = INT8_MAX;

    for (int i = 0; i < giftsCount; ++i) {

        Mountings* mountings = GetById(Mountings, MOUNTINGS, gifts[i]);

        if(tot <= bound2) {
            if(mountings->price <= 100 && mountings->amount < lowAmount) {
                lowAmount = mountings->amount;
                lowId = gifts[i];
            }
        } else {
            if(mountings->price > 100 && mountings->amount < lowAmount) {
                lowAmount = mountings->amount;
                lowId = gifts[i];
            }
        }
    }

    return lowId;

}

bool insertGift(int sellingRecordIds[], int sellingRecordCount) {
    int mountingsId = getGift(sellingRecordIds, sellingRecordCount);

    //sellingRecord有误
    if(mountingsId == -1)
        return false;

    //无合适礼品可送
    if(mountingsId == -2)
        return true;

    //价格太低不送礼品
    if(mountingsId == -3)
        return true;

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
    Insert_sellingRecord(&newSellingRecord);
    mountings->amount--;
}