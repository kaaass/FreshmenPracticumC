//
// Created by guyis on 2019/3/25.
//
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "FileUtil.h"

/**
 * 将字符串写至文件（覆盖）
 * @param filename
 * @param content
 */
void writeStringToFile(char *filename, stringbuf content) {
    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        fprintf(f, "%s", U8_CSTR(content));
        fflush(f);
        fclose(f);
    }
}

/**
 * 从文件读入字符串
 * @param filename
 * @return
 */
stringbuf readStringFromFile(char *filename) {
    assert(isExist(filename));
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return $init$;
    stringbuf content = $init$, line;
    char rawLine[200];
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

/**
 * 创建文件夹
 * @param path
 */
void newFolder(char *path) {
    if (isExist(path))
        return;
    if (MKDIR(path) == -1) {
        fprintf(stderr, "Error creating dir: %s, %d\n", path, errno);
    }
}