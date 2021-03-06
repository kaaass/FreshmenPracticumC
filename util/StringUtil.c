//
// Created by guyis on 2019/3/18.
//

#include <stdio.h>
#include "StringUtil.h"

#ifdef _WIN32

#include <stringapiset.h>

#endif // _WIN32

/**
 * 判断字符串是否为空
 * @param str
 * @return
 */
bool empty(stringbuf str) {
    if (str == NULL)
        return true;
    return length(str) == 0;
}

/**
 * 转换为整数字符串
 * @param val
 * @return
 */
stringbuf toIntString(int val) {
    char buf[100];
    sprintf(buf, "%d", val);
    return newString(buf);
}

/**
 * 将浮点数转为人民币字符串
 * @param val
 * @return
 */
stringbuf toRmbString(double val) {
    char buf[100];
    sprintf(buf, " %.2lf", val);
    return concat(2, LITERAL("￥"), STRING(buf));
}

#ifdef _WIN32

char *gbkToUTF8(char *lpGBKStr) {
    wchar_t *lpUnicodeStr = NULL;
    char *lpUTF8Str;
    int nRetLen = 0, nUTF8StrLen;
    if (!lpGBKStr) return NULL;
    nRetLen = MultiByteToWideChar(CP_ACP, 0, (char *) lpGBKStr, -1, NULL, 0);
    lpUnicodeStr = malloc(sizeof(WCHAR) * (nRetLen + 1));
    nRetLen = MultiByteToWideChar(CP_ACP, 0, (char *) lpGBKStr, -1, lpUnicodeStr, nRetLen);
    if (!nRetLen) {
        if (lpUnicodeStr)
            free(lpUnicodeStr);
        return 0;
    }
    nRetLen = WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);
    nUTF8StrLen = nRetLen + 1;
    lpUTF8Str = malloc(sizeof(char) * nUTF8StrLen);
    nRetLen = WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *) lpUTF8Str, nUTF8StrLen, NULL,
                                  NULL);
    if (lpUnicodeStr)
        free(lpUnicodeStr);
    return lpUTF8Str;
}

/**
 * 读入一行字符串
 * @return
 */
stringbuf readLine() {
    char buf[100], *result;
    gets(buf);
    result = gbkToUTF8(buf);
    return newString(result);
}

#else
/**
 * 读入一行字符串
 * @return
 */
stringbuf readLine() {
    char buf[100];
    fgets(buf, 99, stdin);
    return newString(buf);
}
#endif // _WIN32