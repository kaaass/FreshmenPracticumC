//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "../../data/DataManager.h"
#include "About.h"
#include "View.h"
#include "AppendOrder.h"
#include "RecordInput.h"
#include "StatisticsSituation.h"
#include "MassIncrease.h"
#include "Browsing.h"
#include "ViewPurchase.h"

#define MENU_CNT 7

Menu *mainMenu;

void updateIntro();

void Welcome_init() {
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    新增记录"),
            STR_BUF("    批量增加"),
            STR_BUF("    浏览记录"),
            STR_BUF("    统计信息"),
            STR_BUF("     设  置"),
            STR_BUF("     关  于"),
            STR_BUF("    退出系统")
    };
    mainMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_WELCOME, STR_BUF("首页"));
    ViewPurchase_init();
}

void Welcome_inLoop() {
    Menu_inLoop(mainMenu);
    if (READ_SPEC) {
        updateIntro();
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键进入菜单
            switch (mainMenu->cur) {
                case 0:
                    AppendOrder_init();
                    break;
                case 1:
                    MassIncrease_init();
                    break;
                case 2:
                    View_init();
                    break;
                case 3:
                    StatisticsSituation_init();
                    break;
                case 5:
                    About_init();
                    break;
                case 6:
                    DataManager_save(LITERAL("data"));
                    exit(0);
                default:
                    break;
            }
        }
    }
}

int Welcome_render(int line) {
    UI_printMidString(LITERAL("欢迎使用进销存系统!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    UI_printMidString(LITERAL("本程序为程序设计基础课程设计项目 (2018级)的实现"), line);
    line += 1;
    // 主菜单
    line += Menu_render(mainMenu, line);
    updateIntro();
    return line;
}

void updateIntro() {
    string instruction = NULL;
    // 根据菜单选择项更新说明
    switch (mainMenu->cur) {
        case 0:
            instruction = LITERAL("向数据库添加一条购买/进货记录。");
            break;
        case 1:
            instruction = LITERAL("从文件中读入，并向数据库添加若干条购买/进货记录。");
            break;
        case 2:
            instruction = LITERAL("浏览、修改数据库中的数据。");
            break;
        case 3:
            instruction = LITERAL("统计数据库的各类信息。");
            break;
        case 4:
            instruction = LITERAL("设置程序的一些信息。");
            break;
        case 5:
            instruction = LITERAL("查看本程序开发者的相关信息。");
            break;
        case 6:
            instruction = LITERAL("退出程序并保存当前数据库。");
            break;
        default:
            instruction = LITERAL("");
    }
    UI_setFooterUpdate(instruction);
}