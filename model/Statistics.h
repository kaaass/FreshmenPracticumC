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

//Database * GIFT = NULL;

typedef struct Report {
    enum MountingsType type;
    int amount;
}Report;

typedef struct Any_gift{
    int amount;
    double total;
    Time time;
    Guest guest;
}Any_gift;

typedef struct Present_Situation {
    Time time_recording;
    int amount;////对应零件的个数.
    Guest people;
    double  AMOUNT;////这是礼物钱数
    enum MountingsType type;
}Present_Situation;

double Purchase_total();////得到所有进货的价钱

double Sell_total();////得到销售额

double Profits();////得到总利润

Database * sort_gift();//输出礼物总情况

Database * Search_gift(enum MountingsType type);//查询某个礼物情况

Database * Print_Sellingrecord(Time a,Time b);//按照时间顺序查找销售记录

Database * Print_Purchaserecord(Time a,Time b);//按照时间顺序查找购买记录


#endif //FRESHMAN_PROJ_C_STATISTIC_H
