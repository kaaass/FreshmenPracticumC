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
#include "BRtime.h"
#include "../../model/Consultation.h"

Menu *timeMenu;

Table *dataTable;

void BRtime_init(){
    stringbuf columnName[] = {
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF("")
    };
    int columnWidth[] = {24, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
}

void BRtime_inLoop(){
    Menu_inLoop(timeMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ENTER)
            ;
    }
}

int BRtime_render(int line){
    UI_printMidString(LITERAL("请输入所查询的时间段："), line);
    line += 1;
    putchar('\n');
    line += 1;
    line += Menu_render(timeMenu, line);
    string instruction = LITERAL("请输入所查询的时间段：");
    UI_setFooterUpdate(instruction);
    return line;
}