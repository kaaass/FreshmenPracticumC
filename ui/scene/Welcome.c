//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"

Menu *mainMenu;

void Welcome_init() {
    NOW_SCENE = SCENE_WELCOME;
    TITLE = STR_BUF("进销存系统 v1.0");
    BreadCrumb_enter(STR_BUF("首页"));
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("新增记录"),
            STR_BUF("批量增加"),
            STR_BUF("删除记录"),
            STR_BUF("退出系统")
    };
    mainMenu = Menu_create(name, 4, 0, NULL);
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

int Welcome_render() {
    int lineCnt = 0;
    stringbuf info = UI_midString(LITERAL("欢迎使用本系统！"));
    printf("%s\n", CSTR(info));
    lineCnt += 1;
    // 主菜单
    lineCnt += Menu_render(mainMenu);
    return lineCnt;
}