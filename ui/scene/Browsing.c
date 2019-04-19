//
// Created by St on 2019-04-14.
//

#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "../Menu.h"
#include "../../data/Serializer.h"
#include "../../data/DataManager.h"
#include "Browsing.h"
#include "View.h"
#include "../Table.h"
#include "../../model/Consultation.h"
#include "BRmountings.h"
#include "BRseller.h"
#include "BRguest.h"
#include "BRtime.h"

#define MENU_CNT 4

#define menu 101
#define form 102

int tem = 101;

Menu *mMenu;

void updatePrintf();
void menu_inLoop();
void form_inLoop();

Table *dataTable;

void Browsing_init(){
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("  配  件"),
            STR_BUF("  供货商"),
            STR_BUF("  客  户"),
            STR_BUF("  时  间"),
    };
    stringbuf columnName[] = {
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF("")
    };
    mMenu = Menu_create(-7, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_BROWSING, STR_BUF("浏览记录"));
    //表格
    int columnWidth[] = {24, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 0, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
}

void Browsing_inLoop(){
    Menu_inLoop(mMenu);
    if (READ_SPEC) {
        updatePrintf();
//        if(SPEC_KEY == KEY_TAB&&tem == menu){
//            tem = form;
//        }
//        else
            tem = menu;
//        if(tem == menu){
//                menu_inLoop();
//            }
//        else
//                form_inLoop();
        if(SPEC_KEY == KEY_ESC){
            UI_endScene();
        }
    }
}

int  Browsing_render(int line){
    UI_printMidString(LITERAL("欢迎使用浏览记录!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    line += Menu_render(mMenu, line);
    updatePrintf();
    return line;
}

void updatePrintf(){
    string instruction = NULL;
    switch (mMenu->cur) {
        case 0:
            instruction = LITERAL("查询某个配件的购买/进货记录。");
            break;
        case 1:
            instruction = LITERAL("查询某个进货商的进货记录。");
            break;
        case 2:
            instruction = LITERAL("查询某个客户的购买记录。");
            break;
        case 3:
            instruction = LITERAL("查询某段时间的购买/进货记录。");
            break;
        default:
            instruction = LITERAL("");
    }
    UI_setFooterUpdate(instruction);
}

void menu_inLoop(){
    if (SPEC_KEY == KEY_ENTER) {
        switch (mMenu->cur) {
            case 0:
                BRmountings_init();
                break;
            case 1:
                BRseller_init();
                break;
            case 2:
                BRguest_init();
                break;
            case 3:
                BRtime_init();
                break;
            case 4:
                DataManager_save(LITERAL("data"));
                exit(0);
            default:
                break;
        }
    }
}

void form_inLoop(){
    Table_inLoop(dataTable);
    UI_setFooterUpdate(Table_getSelection(dataTable));
}


