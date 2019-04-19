//
// Created by St on 2019-04-19.
//

#include <stdio.h>
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "../Menu.h"
#include "../../data/Serializer.h"
#include "../../data/DataManager.h"
#include "../cJson/cJSON.h"
#include "../../util/FileUtil.h"
#include "BRmountings.h"
#include "../Table.h"
#include "BRmountingsin.h"
#include "BRmountingsout.h"

#define MENU_CNT 2

Menu *mountingMenu;

Table *dataTable;

void BRmountings_init(){
    stringbuf mountings_name[] = {
            STR_BUF("    购买记录"),
            STR_BUF("    进货记录"),
    };
    stringbuf columnName[] = {
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF("")
    };
    mountingMenu = Menu_create(-1, 3, mountings_name, MENU_CNT, 0);
    UI_startScene(SCENE_BRMOUNTINGS, STR_BUF("查询零配件"));
    int columnWidth[] = {24, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
}

void BRmountings_inLoop(){
    Menu_inLoop(mountingMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键进入菜单
            switch (mountingMenu->cur) {
                case 0:
                    BRmountingsin_init();
                    break;
                case 1:
                    BRmountingsout_init();
                    break;
                case 2:
                    DataManager_save(LITERAL("data"));
                    exit(0);
                default:
                    break;
            }
        }
        if(SPEC_KEY == KEY_ESC)
            UI_endScene();
    }
}

int BRmountings_render(int line){
    UI_printMidString(LITERAL("欢迎使用浏览记录!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    line += Menu_render(mountingMenu, line);
    return line;
}

