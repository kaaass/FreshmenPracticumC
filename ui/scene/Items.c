//
// Created by hasee on 2019/4/13.
//

#include <stdio.h>
#include "Items.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "../../util/Time.h"
#include "../../model/Statistics.h"
#include "../../externals/cstring_jslike/cstring_jslike.h"
#include "../Table.h"

Table *dataTable;

void Items_init(int type){
    stringbuf columnName[] = {
            STR_BUF("时间"),
            STR_BUF("品牌"),
            STR_BUF("数量"),
            STR_BUF("客人"),
            STR_BUF("手机号"),
            STR_BUF("价值")
    };
    Database *create = Search_gift(type);
    int i=0,num=0;
    ForEach(cur, create){num++;}
    stringbuf testData[num][6];
    ForEach(cur, create){
        Present_Situation *now = GetData(Present_Situation, cur);
        Mountings *rec_mountings = GetById(Mountings,MOUNTINGS,now->partId);
        char ch1[1000],ch2[1000];
        testData[i][0] = Time_toLocalString(now->time_recording);
        testData[i][1] = rec_mountings->name;
        testData[i][2] = newString(itoa(now->amount,ch1,10));
        testData[i][3] = now->people.name;
        testData[i][4] = now->people.phone;
        testData[i][5] = newString(itoa((int)now->AMOUNT,ch2,10));
        i++;
    };
    int columnWidth[] = {21, 10, 8, 21,22,12};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
    for (int j = 0; j < num; j++) Table_pushLine(dataTable, testData[j]);
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Enter键以返回..."));
    switch (type){
        case 0:
            UI_startScene(SCENE_ITEMS, STR_BUF("鼠标"));
            break;
        case 1:
            UI_startScene(SCENE_ITEMS, STR_BUF("键盘"));
            break;
        case 2:
            UI_startScene(SCENE_ITEMS, STR_BUF("内存"));
            break;
        case 3:
            UI_startScene(SCENE_ITEMS, STR_BUF("显卡"));
            break;
        case 4:
            UI_startScene(SCENE_ITEMS, STR_BUF("硬盘"));
            break;
        case 5:
            UI_startScene(SCENE_ITEMS, STR_BUF("CPU"));
            break;
        case 6:
            UI_startScene(SCENE_ITEMS, STR_BUF("显示器"));
            break;
        default:
            break;
    }
    //UI_startScene(SCENE_ITEMS, STR_BUF("礼物总情况"));
}

void Items_inLoop(){
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键返回
            UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
            UI_endScene();
        }
    }
}

int Items_render(int line){
    Table_render(dataTable, line);
}