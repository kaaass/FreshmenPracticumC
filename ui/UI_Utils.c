//
// Created by guyis on 2019/4/9.
//

#include "UI_Utils.h"
#include "UI.h"

#ifndef _WIN32
int getch(void) {
    return 0;
}
#endif

/**
 * 返回居中字符串
 * @param str
 * @return
 */
stringbuf UI_midString(stringbuf str) {
    size_t blanks = ((CON_WIDTH - str->unitCnt) / 2);
    return concat(2, repeat(LITERAL(" "), blanks), str);
}