//
// Created by guyis on 2019/3/25.
//

#ifndef FRESHMAN_PROJ_C_FILEUTIL_H
#define FRESHMAN_PROJ_C_FILEUTIL_H

#include "StringUtil.h"

void writeStringToFile(char *filename, stringbuf content);
stringbuf readStringFromFile(char *filename);
bool isExist(char *path);

#endif //FRESHMAN_PROJ_C_FILEUTIL_H
