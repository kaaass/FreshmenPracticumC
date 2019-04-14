
//
// Created by hasee on 2019/4/9.
//
#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "StatisticsSituation.h"
#include "Profit.h"
#include "TotalGift.h"
#include "Singleitem.h"
Menu *statMenu;

void StatisticsSituation_init() {
    READ_SPEC = true;//是否读入上下左右键，读入字符串就要false
    stringbuf name[] = {
            STR_BUF("    利润"),
            STR_BUF("    礼物总情况"),
            STR_BUF("    单个礼物查询")
    };
    statMenu = Menu_create(-1, 4, name, 3, 0);
    UI_startScene(SCENE_STATISTICS_SITUATION, STR_BUF("统计信息"));
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
}

void StatisticsSituation_inLoop(){
    Menu_inLoop(statMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ESC){
            UI_endScene();
        }
        if (SPEC_KEY == KEY_ENTER){
            switch (statMenu->cur){
                case 0:
                    Profit_init();
                    break;
                case 1:
                    TotalGift_init();
                    break;
                case 2:
                    Singleitem_init();
                    break;
                default:
                    break;
            }
        }
    }
}

int StatisticsSituation_render(int line){
    UI_printMidString(LITERAL("统计信息"), line++);
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    line += Menu_render(statMenu, line);
    return line;
}