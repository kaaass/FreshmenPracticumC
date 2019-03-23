//
// Created by guyis on 2019/3/19.
//
#include "Time.h"
#include "StringUtil.h"

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
    struct tm *data = gmtime(&now); // UTC 时间
    result.month = data->tm_mon + 1;
    result.day = data->tm_mday;
    result.hour = data->tm_hour;
    result.minute = data->tm_min;
    result.second = data->tm_sec;
    result.timeStamp = now;
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
 * 将时间结构体转为字符串形式
 * @param structTime
 * @return
 */
stringbuf Time_toLocalString(Time structTime) {
    // TODO: 修正为要求的格式
    return newString(asctime(localtime(&structTime.timeStamp)));
}