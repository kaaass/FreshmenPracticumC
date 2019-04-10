//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"

#define MENU_CNT 4

Menu *mainMenu;

void updateIntro();

void Welcome_init() {
    NOW_SCENE = SCENE_WELCOME;
    BreadCrumb_enter(STR_BUF("首页"));
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    新增记录"),
            STR_BUF("    批量增加"),
            STR_BUF("    删除记录"),
            STR_BUF("    退出系统")
    };
    mainMenu = Menu_create(20, 3, name, MENU_CNT, 0);
    updateIntro();
}

void Welcome_inLoop() {
    Menu_inLoop(mainMenu);
    if (READ_SPEC) {
        updateIntro();
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
    freeAssign(&info, UI_midString(LITERAL("本程序为程序设计基础课程设计项目 (2018级)的实现。")));
    printf("\n%s\n", CSTR(info));
    $STR_BUF(info);
    line += 2;
    // 主菜单
    line += Menu_render(mainMenu, line);
    return line;
}

void updateIntro() {
    string instruction = NULL;
    switch (mainMenu->cur) {
        case 0:
            instruction = LITERAL("向数据库添加一条购买/进货记录。");
            break;
        case 1:
            instruction = LITERAL("向数据库添加若干条购买/进货记录，支持从文件中读入。");
            break;
        case 2:
            instruction = LITERAL("删除一条数据库中的购买/进货记录。");
            break;
        case 3:
            instruction = LITERAL("退出程序并保存当前数据库。");
            break;
        default:
            instruction = LITERAL("");
    }
    UI_setFooterUpdate(instruction);
}