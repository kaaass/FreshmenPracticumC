
//
// Created by hasee on 2019/4/9.
//
#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "StatisticsSituation.h"

Menu *mainMenu;

void StatisticsSituation_init() {
    UI_startScene(SCENE_STATISTICS_SITUATION, STR_BUF("统计信息"));
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
    stringbuf name[] = {
            STR_BUF("    利润"),
            STR_BUF("    礼物总情况"),
            STR_BUF("    单个礼物查询")
    };
    mainMenu = Menu_create(-1, 4, name, 3, 0);
    UI_startScene(SCENE_STATISTICS_SITUATION, STR_BUF("关于"));
    READ_SPEC = true;//是否读入上下左右键，读入字符串就要false
}

void StatisticsSituation_inLoop(){
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ESC){
            UI_endScene();
        }
        if (SPEC_KEY == KEY_ENTER){
            switch (mainMenu->cur){
                case 0:

                    break;
                case 1:

                    break;
                case 2:

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
    line += Menu_render(mainMenu, line);
    return line;
}