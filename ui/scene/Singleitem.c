//
// Created by hasee on 2019/4/13.
//
#include "Singleitem.h"
#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "../../model/Statistics.h"
#include "../Table.h"
Menu *singleMenu;
Table *dataTable;

void Singleitem_init(){
    READ_SPEC = true;//是否读入上下左右键，读入字符串就要false
    stringbuf columnName[] = {
            STR_BUF("名称"),
            STR_BUF("种类"),
            STR_BUF("总价值"),
            STR_BUF("数量")
    };
    Database *create = Search_amount_gift();
    int i=0,num=0;
    ForEach(cur, create){num++;}
    stringbuf testData[num][4];
    ForEach(cur, create){
        SingleGift *now = GetData(SingleGift, cur);
        testData[i][0] = now->name;
        testData[i][1] = Mountings_getTypeString(now->type);
        char ch1[100];
        sprintf(ch1,"%.2lf",now->total);
        testData[i][2] = newString(ch1);
        char ch2[100];
        sprintf(ch2,"%d",now->amount);
        testData[i][3] = newString(ch2);
        i++;
    };
    int columnWidth[] = {10, 10, 10,10};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 4);
    for (int j = 0; j < num; j++) Table_pushLine(dataTable, testData[j]);
    UI_startScene(SCENE_SINGLEITEM, STR_BUF("单个浏览"));
    UI_setFooterUpdate(LITERAL("按Enter键返回上一页"));

}

void Singleitem_inLoop() {
    Menu_inLoop(singleMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
            UI_endScene();
        }
    }
}

int Singleitem_render(int line){
    Table_render(dataTable, line);
}