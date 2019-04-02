//
// Created by guyis on 2019/3/18.
//

#include "StringUtil.h"

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