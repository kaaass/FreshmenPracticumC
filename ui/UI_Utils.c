//
// Created by guyis on 2019/4/9.
//

#include <string.h>

#include "UI_Utils.h"
#include "UI.h"

/**
 * 字符串显示长度计算
 * @param str
 * @return
 */
size_t UI_stringWidth(stringbuf str) {
    return strlen(CSTR(str));
}

/**
 * 返回居中字符串
 * @param str
 * @return
 */
stringbuf UI_midString(stringbuf str) {
    size_t blanks = CON_WIDTH / 2 - UI_stringWidth(str) / 2;
    return concat(2, repeat(LITERAL(" "), blanks), str);
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