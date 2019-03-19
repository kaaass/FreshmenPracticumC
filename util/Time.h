//
// Created by Kevin on 2019/3/19.
//
#include <time.h>
#include <stdio.h>

#ifndef FRESHMAN_PROJ_C_TIME_H
#define FRESHMAN_PROJ_C_TIME_H
//time_t now=time(NULL);

typedef struct {
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int timeStamp;
} Time;


Time Time_parseTime(time_t now)
{
    static Time timel;
    now=time(NULL);
    if(now==NULL)
    {
        printf("录入时间错误\n");
        return;
    }
    struct tm Date=localtime(&now);
    timel.month=Date.tm_mon+1;
    timel.day=Date.tm_mday;
    timel.hour=Date.tm_hour;
    timel.minute=Date.tm_min;
    timel.second=Date.tm_sec;
    timel.timeStamp=(int)now-1546272000;
    return timel;
}





/*void Time_parseTime(time_t now,Time time);//此函数不直接使用
void Time_getNow(Time TIME);//将时间结构体调入




void Time_getNow(Time TIME)
{
    time_t now=time(NULL);
    return Time_parseTime(now,TIME);
}
void Time_parseTime(time_t now,Time *time)
{
    if(now==NULL)
    {
        printf("录入时间错误\n");
        return;
    }
    struct tm Date=localtime(&now);
    *time.month=Date.tm_mon+1;
    *time.day=Date.tm_mday;
    *time.hour=Date.tm_hour;
    *time.minute=Date.tm_min;
    *time.second=Date.tm_sec;
    *time.timeStamp=(int)now-1546272000;
}*/


#endif //FRESHMAN_PROJ_C_TIME_H
