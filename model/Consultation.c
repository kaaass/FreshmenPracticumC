//
// Created by St on 2019-03-26.
//

#include "Consultation.h"
#include "../data/TableMountings.h"
#include "../data/TableSellingRecord.h"
#include "../data/DataManager.h"
#include <stdbool.h>

//查询某种配件的进货/销售信息
PurchaseRecord *accessoryin[1000];
SellingRecord *accessoryout[1000];
extern Database *PURCHASE_RECORD;
extern Database *SELLING_RECORD;
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


PurchaseRecord **AccessoryIn(int type){
    int num = 0;
    ForEach(cur,PURCHASE_RECORD){
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        if(record->partId == type){      //缺少partId转换type的函数
            accessoryin[num] = record;
            num++;
        }
    }
    qsort(accessoryin ,num , sizeof(PurchaseRecord*) ,comparePurchaseRecord);
    return accessoryin;
}

SellingRecord **AccessoryOut(int type){
    int num = 0;
    ForEach(cur,SELLING_RECORD){
        SellingRecord *record = GetData(SellingRecord, cur);
        if(record->partId == type){
            accessoryout[num] = record;
            num++;
        }
    }
    qsort(accessoryout ,num , sizeof(SellingRecord*) ,compareSellingRecord);
    return accessoryout;
}

//查询某个供货商的历史进货信息
PurchaseRecord *supplier[1000];
PurchaseRecord **Supplier(int sellerId){
    int num = 0;
    ForEach(cur,PURCHASE_RECORD){
        PurchaseRecord *record = GetData(PurchaseRecord,cur);
        if(record->sellerId == sellerId){
            supplier[num] = record;
            num++;
        }
    }
    qsort(supplier,num, sizeof(PurchaseRecord*),comparePurchaseRecord);
    return supplier;
}

//查询某个客户的历史采购信息
SellingRecord *guest[1000];
SellingRecord **Client(int guestId){
    int num = 0;
    ForEach(cur,SELLING_RECORD){
        SellingRecord *record = GetData(SellingRecord,cur);
        if(record->guestId ==guestId){
            guest[num] = record;
            num++;
        }
    }
    qsort(guest,num, sizeof(SellingRecord*),compareSellingRecord);
    return guest;
}