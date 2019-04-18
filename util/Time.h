//
// Created by Kevin on 2019/3/19.
//
#include <time.h>
#include <stdio.h>

#include "StringUtil.h"

#ifndef FRESHMAN_PROJ_C_TIME_H
#define FRESHMAN_PROJ_C_TIME_H
//time_t now=time(NULL);

/**
 * 结构体：时间
 */
typedef struct {
    int month;
    int day;
    int hour;
    int minute;
    int second;
    time_t timeStamp;
} Time;

Time Time_parseTime(time_t now);
Time Time_getNow();
bool Time_isValid(Time structTime);
stringbuf Time_toLocalString(Time structTime);
Time Time_getTimestamp(Time sTime);

#endif //FRESHMAN_PROJ_C_TIME_H
