//
// Created by guyis on 2019/4/2.
//

#include "unity.h"

#include "../data/DataManager.h"
#include "../util/StringUtil.h"
#include "../data/TableSellingRecord.h"
#include "../data/TablePurchaseRecord.h"
#include "../model/Statistics.h"
#include "../util/Time.h"

void test_statistics(){
    printf("%lf\n",Purchase_total());
    printf("%lf\n",Sell_total());
    printf("%lf\n",Profits());
}

void test_gift_situation(){
    Database *db=sort_gift();
    ForEach(cur, db){
        Present_Situation *now = GetData(Present_Situation, cur);
        stringbuf timeStr = Time_toLocalString(now->time_recording);
        printf("type=%d,AMOUNT=%lf,Guest=%d,amount=%d,time=%s",now->type,now->AMOUNT,now->people.phone,now->amount,CSTR(timeStr));
        $STR_BUF(timeStr);
    }
    Database_destroy(db);
}

void test_search_gift(){
    Database *db=Search_gift(1);
    ForEach(cur, db){
        Present_Situation *now = GetData(Present_Situation, cur);
        stringbuf timeStr = Time_toLocalString(now->time_recording);
        printf("type=%d,AMOUNT=%lf,Guest=%d,amount=%d,time=%s",now->type,now->AMOUNT,now->people.phone,now->amount,CSTR(timeStr));
        $STR_BUF(timeStr);
    }
    Database_destroy(db);
}

void test_time_search_gift(){
        Time a = Time_parseTime(1553011043);
        Time b = Time_parseTime(1553011344);
    Database *db=Print_Sellingrecord(a, b);
    ForEach(cur, db) {
        SellingRecord *now = GetData(SellingRecord, cur);
        stringbuf timeStr = Time_toLocalString(now->time);
        printf("Selling Record {Id = %d, partId = %d, status = %d, guestId = %d,amount = %d,total = %f,orderId = %d,time = %s}\n",
               now->id, now->partId,
               now->status, now->guestId, now->amount, now->total, now->orderId,
               CSTR(timeStr));
        $STR_BUF(timeStr);
    }
    Database_destroy(db);
}

int main() {
    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));


    RUN_TEST(test_statistics);
    RUN_TEST(test_gift_situation);
    RUN_TEST(test_search_gift);
    RUN_TEST(test_time_search_gift);

    DataManager_finalize();

    return UNITY_END();
}