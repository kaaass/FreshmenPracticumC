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
#include "Statistics.h"
#include "../externals/cstring_jslike/cstring_jslike.h"

#define type_num 5//零部件的种类数


int compareGift_situation(const void *a, const void *b) {
    time_t tsA = (*(Present_Situation **) a)->time_recording.timeStamp,
            tsB = (*(Present_Situation **) b)->time_recording.timeStamp;
    return tsB - tsA;
}

int _comparePurchaseRecord(const void *a, const void *b) {
    time_t tsA = (*(PurchaseRecord **) a)->time.timeStamp,
            tsB = (*(PurchaseRecord **) b)->time.timeStamp;
    return tsB - tsA;
}

int _compareSellingRecord(const void *a, const void *b) {
    time_t tsA = (*(SellingRecord **) a)->time.timeStamp,
            tsB = (*(SellingRecord **) b)->time.timeStamp;
    return tsB - tsA;
}

double Purchase_total() {
    double total = 0;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        if (record->status == PURCHASE_NORMAL || record->status == PURCHASE_SALES_RETURN)
            total = record->total + total;
    }
    return total;
}//得到所有进货的价钱

double Sell_total() {
    double total = 0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        if (record->status == SELLING_NORMAL || record->status == SELLING_SALES_RETURN)
            total = record->total + total;
    }
    return total;
}//得到销售额

double Profits() { return Sell_total() - Purchase_total(); }//得到总利润


Database *Gift_situation() {
    Database *GIFT = NULL;
    GIFT = Create(Present_Situation);
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        Guest *rec_guest = GetById(Guest, GUEST, record->guestId);
        Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, record->partId);
        if (record->status == 3) {
            Present_Situation temp = {
                    .time_recording=record->time,
                    .amount=record->amount,
                    .people=*rec_guest,
                    .AMOUNT=record->total,
                    //.type = rec_mountings->type
                    .partId=record->partId
            };
            Database_pushBack(GIFT, Data(Present_Situation, &temp));
        }
    }
    return GIFT;
}//这是得到礼物的总情况,下面输出特定的礼物要提前用此函数

Database *sort_gift() {
    Database *GIFT = Gift_situation();
    Present_Situation *gift_situation[1000];
    int num = 0;
    ForEach(cur, GIFT) {
        Present_Situation *record = GetData(Present_Situation, cur);
        gift_situation[num] = record;
        num++;
    }
    qsort(gift_situation, num, sizeof(Present_Situation *), compareGift_situation);
    return arrayToDatabase(Data(Present_Situation, gift_situation), num);
}//直接用此函数即可，上面Gift_situation()不用用；

Database *Print_Sellingrecord(Time a, Time b) {
    if (a.timeStamp > b.timeStamp) {
        Time c = a;
        a = b;
        b = c;
    }
    SellingRecord *temp[1000], *temp1[500];
    int num = 0, num1 = 0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        if(record->status==0||record->status==2)
        {
            temp[num] = record;
            num++;
        }
    }
    qsort(temp, num, sizeof(SellingRecord *), _compareSellingRecord);
    int ii = 0;
    while (num1 < num) {
        if (temp[num1]->time.timeStamp >= a.timeStamp && temp[num1]->time.timeStamp <= b.timeStamp) {
            temp1[ii] = temp[num1];
            ii++;
        }
        num1++;
    }
    return arrayToDatabase(Data(SellingRecord, temp1), ii);
}//按照时间顺序查找销售记录

Database *Print_Purchaserecord(Time a, Time b) {
    if (a.timeStamp > b.timeStamp) {
        Time c = a;
        a = b;
        b = c;
    }
    PurchaseRecord *temp[1000], *temp1[500];
    int num = 0, num1 = 0;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        if(record->status==0||record->status==2 || record->status == SELLING_GIFT)
        {
            temp[num] = record;
            num++;
        }
    }
    qsort(temp, num, sizeof(PurchaseRecord *), _comparePurchaseRecord);
    int ii = 0;
    while (num1 < num) {
        if (temp[num1]->time.timeStamp >= a.timeStamp && temp[num1]->time.timeStamp <= b.timeStamp) {
            temp1[ii] = temp[num1];
            ii++;
        }
        num1++;
    }
    return arrayToDatabase(Data(PurchaseRecord, temp1), ii);
}//按照时间顺序查找购买记录

Database *SellScatter(enum MountingsType type_scan) {
    Database *SELLSCATTER = NULL;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, record->partId);
        if (type_scan == rec_mountings->type && (record->status == 0 || record->status == 2 || record->status == 3)) {
            SellPot temp = {
                    .type=rec_mountings->type,
                    .price=record->price,
                    .time_pot=record->time
            };
            Database_pushBack(SELLSCATTER, Data(SellPot, &temp));
        }
    }
    return SELLSCATTER;
}////这是得到某货物时间与售价 点

Database *PurchaseScatter(enum MountingsType type_scan) {
    Database *PURCHASESCATTER = NULL;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, record->partId);
        if (type_scan == rec_mountings->type && (record->status == 0 || record->status == 2)) {
            PurchasePot temp = {
                    .type=rec_mountings->type,
                    .price=record->price,
                    .time_pot=record->time
            };
            Database_pushBack(PURCHASESCATTER, Data(PurchasePot, &temp));
        }
    }
    return PURCHASESCATTER;
}////这是得到某货物时间与进价 点

stringbuf typename(int partid) {
    Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, partid);
    return Mountings_getTypeString(rec_mountings->type);
}///得到物品种类

Database *Search_gift(int partid) {
    Database *db = sort_gift();
    Present_Situation *search_gift[1000];
    int num = 0;
    ForEach(cur, db) {
        Present_Situation *record = GetData(Present_Situation, cur);
        Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, record->partId);
        if (partid == record->partId) {
            search_gift[num] = record;
            num++;
        }
    }
    return arrayToDatabase(Data(Present_Situation, search_gift), num);
}//搜索某件物品的情况

Database *Search_amount_gift() {
    Database *AMOUNTGIFT = NULL;
    AMOUNTGIFT = Create(SingleGift);
    int count = 0;
    while (count < 1000) {
        Database *db = Search_gift(count);
        if (db == NULL) {
            count++;
            continue;
        }
        SingleGift searchgift;
        searchgift.total = 0;
        searchgift.amount = 0;
        bool flag = false;
        //double total=0;
        //int amount=0;
        //stringbuf name;
        ForEach(cur, db) {
            flag = true;
            Present_Situation *record = GetData(Present_Situation, cur);
            Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, record->partId);
            searchgift.type = rec_mountings->type;
            searchgift.partId = rec_mountings->id;
            searchgift.total += record->AMOUNT;
            searchgift.amount += record->amount;
        }
        if (flag) {
            Database_pushBack(AMOUNTGIFT, Data(SingleGift, &searchgift));
        }
        count++;
    }
    return AMOUNTGIFT;
}///搜索某件物品的情况,返回值是SingleGift类型的结构体