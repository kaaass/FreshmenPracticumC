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

stringbuf UI_midString(stringbuf);

#endif //FRESHMAN_PROJ_C_UI_UTILS_H
