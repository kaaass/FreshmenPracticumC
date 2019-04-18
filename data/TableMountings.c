//
// Created by guyis on 2019/4/18.
//
#include "TableMountings.h"

/**
 * 获取配件类型对应的字符串名称
 * @param type
 * @return
 */
stringbuf Mountings_getTypeString(enum MountingsType type) {
    switch (type) {
        case MOUNTINGS_MOUSE:
            return STR_BUF("鼠标");
        case MOUNTINGS_KEYBOARD:
            return STR_BUF("键盘");
        case MOUNTINGS_MEMORY:
            return STR_BUF("内存");
        case MOUNTINGS_GRAPHICS_CARD:
            return STR_BUF("显卡");
        case MOUNTINGS_HARD_DISK:
            return STR_BUF("硬盘");
        case MOUNTINGS_CPU:
            return STR_BUF("CPU");
        case MOUNTINGS_SCREEN:
            return STR_BUF("屏幕");
        default:
            return $init$;
    }
}
