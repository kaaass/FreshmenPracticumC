//
// Created by guyis on 2019/3/25.
//
#include <stdio.h>
#include <assert.h>

#include "FileUtil.h"

/**
 * 将字符串写至文件（覆盖）
 * @param filename
 * @param content
 */
void writeStringToFile(char *filename, stringbuf content) {
    FILE *f = fopen(filename, "w");
    fprintf(f, "%s", CSTR(content));
    fflush(f);
}

/**
 * 从文件读入字符串
 * @param filename
 * @return
 */
stringbuf readStringFromFile(char *filename) {
    // assert(isExist(filename)); // FIXME: 在Linux上不工作
    FILE *f = fopen(filename, "r");
    stringbuf content = $init$, line;
    char rawLine[200];
    if (f == NULL) return content;
    while (!feof(f)) {
        fgets(rawLine, 200 - 1, f);
        line = STRING(rawLine);
        freeAssign(&content, concat2(content, line));
    }
    return content;
}

/**
 * 判断路径是否存在
 * @param path
 * @return
 */
bool isExist(char *path) {
    return access(path, F_OK) != -1;
}