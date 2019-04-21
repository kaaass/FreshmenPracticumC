//
// Created by hasee on 2019/4/2.
//


#include "../data/TablePurchaseRecord.h"
#include "../data/TableSellingRecord.h"
#include "../data/TableMountings.h"
#include "../data/DataManager.h"
#include "../core/Database.h"
#include "../util/StringUtil.h"
#include <stdlib.h>
#include "../util/Time.h"
#include "../data/TableGuest.h"
#define type_num 5//零部件的种类数
#ifndef FRESHMAN_PROJ_C_STATISTIC_H
#define FRESHMAN_PROJ_C_STATISTIC_H

#define DATA_TYPE_PurchasePot 10
#define DATA_TYPE_SellPot 11
#define DATA_TYPE_Present_Situation 12
#define DATA_TYPE_SingleGift 13

//Database * GIFT = NULL;

typedef struct PurchasePot{
    enum MountingsType type;
    double price;
    Time time_pot;
}PurchasePot;

typedef struct SellPot{
    enum MountingsType type;
    double price;
    Time time_pot;
}SellPot;

typedef struct Present_Situation {
    Time time_recording;
    int amount;////对应零件的个数.
    Guest people;
    double  AMOUNT;////这是礼物钱数
    int partId;
}Present_Situation;

typedef struct singleGift{
    enum MountingsType type;
    int partId;
    double total;
    int amount;
}SingleGift;

double Purchase_total();////得到所有进货的价钱

double Sell_total();////得到销售额

double Profits();////得到总利润

Database * sort_gift();//输出礼物总情况

Database * Search_gift(int partid);//查询某个礼物情况

Database * Print_Sellingrecord(Time a,Time b);//按照时间顺序查找销售记录

Database * Print_Purchaserecord(Time a,Time b);//按照时间顺序查找购买记录

Database * PurchaseScatter(enum MountingsType type_scan);////这是得到某货物时间与进价 点

Database * SellScatter(enum MountingsType type_scan);////这是得到某货物时间与售价 点

stringbuf typename(int partid);///得到物品种类

Database * Search_amount_gift();///查询礼物总情况

stringbuf typenamebytype(enum MountingsType type);///得到物品种类(通过枚举类型)
#endif //FRESHMAN_PROJ_C_STATISTIC_H
