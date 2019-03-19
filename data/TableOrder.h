//
// Created by hasee on 2019/3/19.
//
#include "../util/StringUtil.h"


#ifndef FRESHMAN_PROJ_C_TABLEORDER_H
#define FRESHMAN_PROJ_C_TABLEORDER_H
#define MaxOPID 100;
enum {Normal=0,Del,SalesReturn,Gift}Status;
enum {Purchase=0,Singlebuy,Wholesale}How;

const int DATA_TYPE_Test = 7;

typedef struct {
    int id;
    How type;
    Status status;
    int opcount;
    int opId[MaxOPID];
    float price;
} Provider;




#endif //FRESHMAN_PROJ_C_TABLEORDER_H
