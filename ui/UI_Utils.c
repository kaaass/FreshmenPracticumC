//
// Created by guyis on 2019/4/9.
//

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "UI_Utils.h"
#include "UI.h"
#include "../util/Time.h"

/**
 * 字符串显示长度计算
 * @param str
 * @return
 */
size_t UI_stringWidth(stringbuf str) {
    return strlen(CSTR(str));
}

/**
 * 打印居中字符串
 * @param str 待打印行
 * @return
 */
void UI_printMidString(stringbuf str, int lineNo) {
    UI_printMidStringAt(str, 0, 0, CON_WIDTH, lineNo);
    putchar('\n');
}

/**
 * 打印任意位置居中字符串
 * @param str 待打印行
 * @param x
 * @param y
 * @param w 宽度
 * @param lineNo
 * @return
 */
void UI_printMidStringAt(stringbuf str, int x, int y, int w, int lineNo) {
    int blanks = w / 2 - UI_stringWidth(str) / 2;
    Position pos = {
            .x = x + blanks,
            .y = y + lineNo
    };
    UI_moveCursor(pos);
    printf("%s", CSTR(str));
}

/**
 * 打印空白
 * @param cnt
 */
void UI_blanks(int cnt) {
    while (cnt--) putchar(' ');
}

/**
 * 读入整数
 * @param num 保存结果的指针
 * @param tip 输入提示，若NULL则为默认
 * @return
 */
bool UI_inputInt(int *num, string tip) {
    bool status;
    assert(num);
    if (tip == NULL)
        tip = LITERAL("请输入整数：");
    UI_setFooterUpdate(tip);
    UI_setCursorVisible(true);
    status = scanf("%d", num) == 1;
    fflush(stdin);
    return status;
}

/**
 * 读入浮点数
 * @param num 保存结果的指针
 * @param tip 输入提示，若NULL则为默认
 * @return
 */
bool UI_inputDouble(double *num, string tip) {
    bool status;
    assert(num);
    if (tip == NULL)
        tip = LITERAL("请输入浮点数：");
    UI_setFooterUpdate(tip);
    UI_setCursorVisible(true);
    status = scanf("%lf", num) == 1;
    fflush(stdin);
    return status;
}

/**
 * 读入时间
 * @param num 保存结果的指针
 * @param tip 输入提示，若NULL则为默认，暂时会忽略
 * @return
 */
bool UI_inputTime(Time *sTime, string tip) {
    // TODO: 改进时间的输入方式
    bool status;
    Time temp;
    assert(sTime);
    status = UI_inputInt(&temp.month, LITERAL("请输入月份："))
            && temp.month >= 1 && temp.month <= 12;
    if (status)
        status &= UI_inputInt(&temp.day, LITERAL("请输入日期："))
                && temp.day >= 1 && temp.day <= 31;
    if (status)
        status &= UI_inputInt(&temp.hour, LITERAL("请输入小时："))
                && temp.hour >= 0 && temp.hour <= 23;
    if (status)
        status &= UI_inputInt(&temp.minute, LITERAL("请输入分钟："))
                && temp.minute >= 0 && temp.minute <= 59;
    if (status)
        status &= UI_inputInt(&temp.second, LITERAL("请输入秒："))
                && temp.second >= 0 && temp.second <= 59;
    *sTime = Time_getTimestamp(temp);
    return status;
}

/**
 * 读入字符串
 * @param str 保存结果的指针
 * @param tip 输入提示，若NULL则为默认
 * @return
 */
stringbuf UI_inputString(string tip) {
    stringbuf str;
    if (tip == NULL)
        tip = LITERAL("请输入字符串：");
    UI_setFooterUpdate(tip);
    UI_setCursorVisible(true);
    str = readLine();
    UI_setCursorVisible(false);
    return str;
}

#ifdef _WIN32

#include <windows.h>

/**
 * 移动控制台光标
 * @param x
 * @param y
 */
void UI_moveCursor(Position pos) {
    HANDLE a;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cos = {(SHORT) pos.x, (SHORT) pos.y};
    SetConsoleCursorPosition(a, cos);
}

/**
 * 获得控制台光标位置
 * @return
 */
Position UI_getCursorPos() {
    Position pos = {0, 0};
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(stdHandle, &csbi)) {
        pos.x = csbi.dwCursorPosition.X;
        pos.y = csbi.dwCursorPosition.Y;
    }
    return pos;
}

/**
 * 设置控制台光标是否可见
 * @param visible
 */
void UI_setCursorVisible(bool visible) {
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cInfo;
    cInfo.dwSize = 1;
    cInfo.bVisible = visible;
    SetConsoleCursorInfo(stdHandle, &cInfo);
}

/**
 * 设置窗口标题
 * @param title
 */
void UI_setTitle(string title) {
    SetConsoleTitle(CSTR(title));
}

/**
 * 设置文本前景&背景色
 * @param color
 */
void UI_setTextColor(short color) {
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(stdHandle, (WORD) color);
}

#else
// 无法于Unix系统实现的函数
int getch(void) {return 0;}
void UI_moveCursor(Position pos) {}
Position UI_getCursorPos() {return (Position) {0, 0};}
void UI_setCursorVisible(bool visible) {}
void UI_setTitle(string title) {}
void UI_setTextColor(short color) {}
#endif // _WIN32
#pragma clang diagnostic pop