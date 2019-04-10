//
// Created by guyis on 2019/4/9.
//

#ifndef FRESHMAN_PROJ_C_UI_UTILS_H
#define FRESHMAN_PROJ_C_UI_UTILS_H

#include "../util/StringUtil.h"

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

#ifndef _WIN32
int getch(void);
#endif // _WIN32

typedef struct {
    int x;
    int y;
} Position;

size_t UI_stringWidth(stringbuf str);

stringbuf UI_midString(stringbuf);

void UI_moveCursor(Position pos);

Position UI_getCursorPos();

void UI_setCursorVisible(bool visible);

void UI_setTitle(string title);

void UI_setTextColor(short color);

#endif //FRESHMAN_PROJ_C_UI_UTILS_H
