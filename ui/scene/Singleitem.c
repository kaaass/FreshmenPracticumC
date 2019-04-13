//
// Created by hasee on 2019/4/13.
//
#include "Singleitem.h"
#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "StatisticsSituation.h"
#include "Profit.h"
#include "TotalGift.h"

Menu *mainMenu;

void Singleitem_init(){
    READ_SPEC = true;//是否读入上下左右键，读入字符串就要false
    stringbuf name[] = {
            STR_BUF("    鼠标"),
            STR_BUF("    键盘"),
            STR_BUF("    内存"),
            STR_BUF("    显卡"),
            STR_BUF("    硬盘"),
            STR_BUF("    CPU"),
            STR_BUF("    显示器")
    };
    mainMenu = Menu_create(-1, 4, name, 7, 0);
    UI_startScene(SCENE_STATISTICS_SITUATION, STR_BUF("统计信息"));
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
}

void StatisticsSituation_inLoop(){
    Menu_inLoop(mainMenu);
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
                default:
                    break;
            }
        }
    }
}