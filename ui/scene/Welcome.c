//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"

Menu *mainMenu;

void Welcome_init() {
    NOW_SCENE = SCENE_WELCOME;
    BreadCrumb_enter(STR_BUF("首页"));
    UI_setFooterUpdate(LITERAL("本程序为程序设计基础课程设计项目 (2018级)的实现。"));
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    新增记录"),
            STR_BUF("    批量增加"),
            STR_BUF("    删除记录"),
            STR_BUF("    退出系统")
    };
    mainMenu = Menu_create(20, 3, name, 4, 0);
}

void Welcome_inLoop() {
    Menu_inLoop(mainMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键进入菜单
            switch (mainMenu->cur) {
                case 3:
                    exit(0);
                default:
                    break;
            }
        }
    }
}

int Welcome_render(int line) {
    stringbuf info = UI_midString(LITERAL("欢迎使用进销存系统！"));
    printf("%s\n", CSTR(info));
    line += 1;
    // 主菜单
    line += Menu_render(mainMenu, line);
    return line;
}