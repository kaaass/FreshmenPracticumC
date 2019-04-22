//
// Created by Kevin on 2019/4/16.
//
#include "Forecase.h"
#include "Forecase.h"

double forecasePurchasePrice(double time, int mountingsId) {
    double xMean = 0;
    double yMean = 0;
    double xyMean = 0;
    double xxMean = 0;
    int cnt = 0;
    double x, y;
    int amount;
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *nowPurchaseRecord = GetData(PurchaseRecord, cur);
        if((nowPurchaseRecord->status == PURCHASE_NORMAL || nowPurchaseRecord->status == PURCHASE_SALES_RETURN) && nowPurchaseRecord->partId == mountingsId) {
            x = (double)nowPurchaseRecord->time.timeStamp;
            y = nowPurchaseRecord->price;
            amount = nowPurchaseRecord->amount;
            xMean += amount * x;
            yMean += amount * y;
            xyMean += amount * x * y;
            xxMean += amount * x * x;
            cnt += amount;
        }
    }

    if(cnt == 1) {
        return yMean;
    }
    if(cnt <= 0) {
        return -1;
    }

    xMean /= cnt;
    yMean /= cnt;
    xyMean /= cnt;
    xxMean /= cnt;

    double m = (xyMean - xMean * yMean) / (xxMean - xMean*xMean);
    double c = yMean - m * xMean;

    double result = m * time + c;
    return result;

}

double forecaseSellingPrice(double time, int mountingsId) {
    double xMean = 0;
    double yMean = 0;
    double xyMean = 0;
    double xxMean = 0;
    double x, y;
    int amount;
    int cnt = 0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *nowSellingRecord = GetData(SellingRecord, cur);
        if((nowSellingRecord->status == SELLING_NORMAL || nowSellingRecord->status == SELLING_SALES_RETURN) && nowSellingRecord->partId == mountingsId) {
            x = (double)nowSellingRecord->time.timeStamp;
            y = nowSellingRecord->price;
            amount = nowSellingRecord->amount;
            xMean += amount * x;
            yMean += amount * y;
            xyMean += amount * x * y;
            xxMean += amount * x * x;
            cnt += amount;
        }
    }

    if(cnt == 1) {
        return yMean;
    }
    if(cnt <= 0) {
        return -1;
    }

    xMean /= cnt;
    yMean /= cnt;
    xyMean /= cnt;
    xxMean /= cnt;

    double m = (xyMean - xMean * yMean) / (xxMean - xMean*xMean);
    double c = yMean - m * xMean;

    double result = m * time + c;
    return result;

}
