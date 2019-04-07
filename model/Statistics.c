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
#define type_num 5//零部件的种类数

#define DATA_TYPE_Report 10
#define DATA_TYPE_Any_gift 11
#define DATA_TYPE_Present_Situation 12

int compareGift_situation (const void * a, const void * b){
    if ( ((Present_Situation*)a)->time_recording.timeStamp <  ((Present_Situation*)b)->time_recording.timeStamp ) return -1;
    if ( ((Present_Situation*)a)->time_recording.timeStamp == ((Present_Situation*)b)->time_recording.timeStamp ) return 0;
    if ( ((Present_Situation*)a)->time_recording.timeStamp >  ((Present_Situation*)b)->time_recording.timeStamp ) return 1;
}
int comparePurchaseRecord (const void * a, const void * b){
    if ( ((PurchaseRecord*)a)->time.timeStamp <  ((PurchaseRecord*)b)->time.timeStamp ) return -1;
    if ( ((PurchaseRecord*)a)->time.timeStamp == ((PurchaseRecord*)b)->time.timeStamp ) return 0;
    if ( ((PurchaseRecord*)a)->time.timeStamp >  ((PurchaseRecord*)b)->time.timeStamp ) return 1;
}
int compareSellingRecord (const void * a, const void * b){
    if ( ((SellingRecord*)a)->time.timeStamp <  ((SellingRecord*)b)->time.timeStamp ) return -1;
    if ( ((SellingRecord*)a)->time.timeStamp == ((SellingRecord*)b)->time.timeStamp ) return 0;
    if ( ((SellingRecord*)a)->time.timeStamp >  ((SellingRecord*)b)->time.timeStamp ) return 1;
}
double Purchase_total() {
    double total=0;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        if (record->status == 0 )
            total = record->total + total;
    }
    return total;
}//得到所有进货的价钱

double Sell_total() {
    double total=0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *record = GetData(SellingRecord, cur);
        if(record->status == 0 )
            total = record->total + total;
    }
    return total;
}//得到销售额

double Profits() {return Sell_total()- Purchase_total();}//得到总利润

Database * GIFT = NULL;
void Gift_situation(){
    //这里应该先销毁原有GIFT
    Database *dele=GIFT;
    GIFT=NULL;
    Database_destroy(dele);
    //extern Database * GIFT = NULL;
    GIFT = Create(Present_Situation);
    ForEach(cur, SELLING_RECORD){
        SellingRecord *record = GetData(SellingRecord, cur);
        Guest *rec_guest = GetById(Guest,GUEST,record->guestId);
        Mountings *rec_mountings = GetById(Mountings,MOUNTINGS,record->partId);
        if(record->status==3)
        {
            Present_Situation temp={
                    .time_recording=record->time,
                    .amount=record->amount,
                    .people=*rec_guest,
                    .AMOUNT=record->total,
                    .type = rec_mountings->type
            };
            Database_pushBack(GIFT,Data(Present_Situation,&temp));
        }
    }
}//这是得到礼物的总情况,下面输出特定的礼物要提前用此函数

Database * sort_gift(){
    Gift_situation();
    Present_Situation * gift_situation[1000];
    int num=0;
    ForEach(cur, GIFT){
        Present_Situation *record = GetData(Present_Situation,cur);
        gift_situation[num] = record;
        num++;
    }
    qsort(gift_situation,num, sizeof(Present_Situation*),compareGift_situation);
    return arrayToDatabase(Data(Present_Situation, gift_situation),num);
}//直接用此函数即可，上面Gift_situation()不用用；

Database * Search_gift(enum MountingsType type){
    Database *db=sort_gift();
    Present_Situation *search_gift[1000];
    int num=0;
    ForEach(cur, db){
        Present_Situation *record = GetData(Present_Situation,cur);
        if(record->type==type)
        {
            search_gift[num]=record;
            num++;
        }
    }
    return arrayToDatabase(Data(Present_Situation, search_gift),num);
}//搜索某件物品的情况

Database * Print_Sellingrecord(Time a,Time b){
    if(a.timeStamp>b.timeStamp)
    {
        Time c=a;a=b;b=c;
    }
    SellingRecord *temp[1000],*temp1[500];
    int num=0,num1=0;
    ForEach(cur,SELLING_RECORD){
        SellingRecord *record = GetData(SellingRecord, cur);
        temp[num] = record;
        num++;
    }
    qsort(temp ,num , sizeof(SellingRecord*) ,compareSellingRecord);
    int ii=0;
    while(num1<num){
        if(temp[num1]->time.timeStamp>=a.timeStamp&&temp[num1]->time.timeStamp>=b.timeStamp)
        {
            temp1[ii]=temp[num1];
            ii++;
        }
        num1++;
    }
    return arrayToDatabase(Data(SellingRecord, temp1),ii);
}//按照时间顺序查找销售记录

Database * Print_Purchaserecord(Time a,Time b){
    if(a.timeStamp>b.timeStamp)
    {
        Time c=a;a=b;b=c;
    }
    PurchaseRecord *temp[1000],*temp1[500];
    int num=0,num1=0;
    ForEach(cur,PURCHASE_RECORD){
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        temp[num] = record;
        num++;
    }
    qsort(temp ,num , sizeof(PurchaseRecord*) ,comparePurchaseRecord);
    int ii=0;
    while(num1<num){
        if(temp[num1]->time.timeStamp>=a.timeStamp&&temp[num1]->time.timeStamp>=b.timeStamp)
        {
            temp1[ii]=temp[num1];
            ii++;
        }
        num1++;
    }
    return arrayToDatabase(Data(PurchaseRecord, temp1),ii);
}//按照时间顺序查找购买记录