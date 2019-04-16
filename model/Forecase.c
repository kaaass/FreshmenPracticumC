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
    ForEach(cur, PURCHASE_RECORD) {
        PurchaseRecord *nowPurchaseRecord = GetData(PurchaseRecord, cur);
        if((nowPurchaseRecord->status == PURCHASE_NORMAL || nowPurchaseRecord->status == PURCHASE_SALES_RETURN) && nowPurchaseRecord->partId == mountingsId) {
            xMean += (double)nowPurchaseRecord->time.timeStamp;
            yMean += nowPurchaseRecord->price;
            xyMean += (double)nowPurchaseRecord->time.timeStamp * nowPurchaseRecord->price;
            xxMean += (double)nowPurchaseRecord->time.timeStamp * nowPurchaseRecord->time.timeStamp;
            cnt++;
        }
    }

    if(cnt <= 1) {
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
    int cnt = 0;
    ForEach(cur, SELLING_RECORD) {
        SellingRecord *nowSellingRecord = GetData(SellingRecord, cur);
        if((nowSellingRecord->status == SELLING_NORMAL || nowSellingRecord->status == SELLING_SALES_RETURN) && nowSellingRecord->partId == mountingsId) {
            xMean += (double)nowSellingRecord->time.timeStamp;
            yMean += nowSellingRecord->price;
            xyMean += (double)nowSellingRecord->time.timeStamp * nowSellingRecord->price;
            xxMean += (double)nowSellingRecord->time.timeStamp * (double)nowSellingRecord->time.timeStamp;
            cnt++;
        }
    }

    if(cnt <= 1) {
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
