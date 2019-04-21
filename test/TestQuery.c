//
// Created by guyis on 2019/4/2.
//

#include "unity.h"

#include "../data/DataManager.h"
#include "../util/StringUtil.h"
#include "../model/Consultation.h"

void test_func() {
}

void test_accessory_in(){
    Database *tem = AccessoryIn(6);
    PurchaseRecord *test;
    ForEach(cur,tem){
        test = GetData(PurchaseRecord,cur);
        printf("%d\t%d\t%d\t%d\n",test->id,test->partId,test->sellerId,test->amount);
    }
}

void test_accessory_out(){
    Database *tem = AccessoryOut(6);
    SellingRecord *test;
    ForEach(cur,tem){
        test = GetData(SellingRecord,cur);
        printf("%d\t%d\t%d\t%d\n",test->id,test->partId,test->guestId,test->amount);
    }
}

void test_supplier() {
    Database *tem = Supplier(7);
    PurchaseRecord *test;
    ForEach(cur, tem) {
        test = GetData(PurchaseRecord, cur);
        printf("%d\t%d\t%d\t%d\n", test->id, test->partId, test->sellerId, test->amount);
    }
}

void test_client(){
    Database *tem = Client(3);
    SellingRecord *test;
    ForEach(cur,tem){
        test = GetData(SellingRecord,cur);
        printf("%d\t%d\t%d\t%d\n",test->id,test->partId,test->guestId,test->amount);
    }
}

void test_query_all_pur(){
    Database *tem = QueryAll_Pur();
    PurchaseRecord *test;
    ForEach(cur, tem) {
        test = GetData(PurchaseRecord, cur);
        printf("%d\t%d\t%d\t%d\n", test->id, test->partId, test->sellerId, test->amount);
    }
}

void test_query_all_sel(){
    Database *tem = QueryAll_Sel();
    SellingRecord *test;
    ForEach(cur,tem){
        test = GetData(SellingRecord,cur);
        printf("%d\t%d\t%d\t%d\n",test->id,test->partId,test->guestId,test->amount);
    }
}

int main() {


    UNITY_BEGIN();

    DataManager_init();
    DataManager_load(LITERAL("inputs/test_database"));

    RUN_TEST(test_func);
    RUN_TEST(test_accessory_in);
    RUN_TEST(test_accessory_out);
    RUN_TEST(test_supplier);
    RUN_TEST(test_client);
    RUN_TEST(test_query_all_pur);
    RUN_TEST(test_query_all_sel);

    DataManager_finalize();

    return UNITY_END();
}