//
// Created by guyis on 2019/3/19.
//
#include "Time.h"
#include "StringUtil.h"
#include <stdlib.h>

#define BJS (+8)

/**
 * 将UTC时间戳解析为Time结构体
 * @param now 待解析时间戳
 * @return Time结构体
 */
Time Time_parseTime(time_t now) {
    Time result = {
            .month = -1,
            .day = -1,
            .hour = -1,
            .minute = -1,
            .second = -1,
            .timeStamp = -1
    };
    if (now == -1) {
        return result;
    }
    result.timeStamp = now;
    now += BJS * 60 * 60;
    struct tm *data = gmtime(&now); // UTC 时间
    result.month = data->tm_mon + 1;
    result.day = data->tm_mday;
    result.hour = data->tm_hour;
    result.minute = data->tm_min;
    result.second = data->tm_sec;
    return result;
}

/**
 * 获取当前时间结构体
 * @return Time结构体
 */
Time Time_getNow() {
    time_t now = time(NULL);
    return Time_parseTime(now);
}

/**
 * 当前时间结构体是否合法
 * @param structTime
 * @return
 */
bool Time_isValid(Time structTime) {
    Time tsSTime = Time_parseTime(structTime.timeStamp);
    if (!(tsSTime.month == structTime.month &&
        tsSTime.day == structTime.day &&
        tsSTime.hour == structTime.hour &&
        tsSTime.minute == structTime.minute &&
        tsSTime.second == structTime.second)) {
        structTime.timeStamp = -1; // 错误
    }
    return structTime.timeStamp != -1;
}

/**
 * 将时间结构体转为字符串形式
 * @param structTime
 * @return
 */
stringbuf Time_toLocalString(Time structTime) {
    char buf[50];
    sprintf(buf, "%02d月%02d日 %02d:%02d:%02d",
            structTime.month, structTime.day, structTime.hour, structTime.minute, structTime.second);
    return newString(buf);
}

/**
 * 获得对应时间的时间戳
 * @param sTime 时间结构体
 * @return
 */
Time Time_getTimestamp(Time sTime) {
    struct tm tmTime = {
            .tm_year = 2019 - 1900,
            .tm_mon = sTime.month - 1,
            .tm_mday = sTime.day,
            .tm_hour = sTime.hour,
            .tm_min = sTime.minute,
            .tm_sec = sTime.second
    };
#ifndef _WIN32
    setenv("TZ", "Asia/Shanghai", 1);
#endif
    time_t ts = mktime(&tmTime);
    sTime.timeStamp = ts;
    return sTime;
}