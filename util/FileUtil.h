//
// Created by guyis on 2019/3/25.
//

#ifndef FRESHMAN_PROJ_C_FILEUTIL_H
#define FRESHMAN_PROJ_C_FILEUTIL_H

#ifdef _WIN32
#include <io.h>

#define MKDIR(dir) mkdir(dir)
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MKDIR(dir) mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif // _WIN32

#include "StringUtil.h"

void writeStringToFile(char *filename, stringbuf content);
stringbuf readStringFromFile(char *filename);
bool isExist(char *path);
void newFolder(char *path);

#endif //FRESHMAN_PROJ_C_FILEUTIL_H
