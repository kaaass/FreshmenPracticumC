//
// Created by hasee on 2019/4/19.
//

#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "Inventory.h"
#include "../UI_Utils.h"
#include "../../data/TableMountings.h"
#include "../../data/DataManager.h"
#include "../../model/Statistics.h"
#include "../Table.h"
Table *dataTable;
void Inventory_init(){
    READ_SPEC = true;
    stringbuf columnName[] = {
            STR_BUF("名称"),
            STR_BUF("种类"),
            STR_BUF("库存")
    };
    int i=0,num=0;
    num = (int)Database_size(MOUNTINGS);
    stringbuf testData[num][3];
    ForEach(cur, MOUNTINGS){
        Mountings *now = GetData(Mountings,cur);
        testData[i][0] = now->name;
        testData[i][1] = Mountings_getTypeString(now->type);
        char ch[100];
        sprintf(ch,"%d",now->amount);
        testData[i][2] = newString(ch);
        i++;
    };
    int columnWidth[] = {10, 10, 10};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 3);
    for(int j = 0;j<num;j++) Table_pushLine(dataTable, testData[j]);
    UI_setFooterUpdate(LITERAL("按下Enter键以返回..."));
    UI_startScene(SCENE_INVENTORY , STR_BUF("库存"));
}

void Inventory_inLoop(){
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            //按回车返回
            UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
            UI_endScene();
        }
    }
}

int Inventory_render(int line){
    Table_render(dataTable,line);
}