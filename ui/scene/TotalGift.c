//
// Created by hasee on 2019/4/11.
//


#include <stdio.h>
#include "TotalGift.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "../../util/Time.h"
#include "../../model/Statistics.h"
#include "../../externals/cstring_jslike/cstring_jslike.h"
#include "../Table.h"
Table *dataTable;

void TotalGift_init(){
    stringbuf columnName[] = {
            STR_BUF("时间"),
            STR_BUF("种类"),
            STR_BUF("品牌"),
            STR_BUF("数量"),
            STR_BUF("客人"),
            STR_BUF("手机号"),
            STR_BUF("价值")
    };
    Database *create = sort_gift();
    int i=0,num=0;
    ForEach(cur, create){num++;}
    stringbuf testData[num][7];
    ForEach(cur, create){
        Present_Situation *now = GetData(Present_Situation, cur);
        Mountings *rec_mountings = GetById(Mountings,MOUNTINGS,now->partId);
        char ch1[1000],ch2[1000];
                testData[i][0] = Time_toLocalString(now->time_recording);
                testData[i][1] = typename(now->partId);
                testData[i][2] = rec_mountings->name;
                char tem1[100];
                sprintf(tem1,"%d",now->amount);
                testData[i][3] = newString(tem1);
                //testData[i][3] = newString(itoa(now->amount,ch1,10));
                testData[i][4] = now->people.name;
                testData[i][5] = now->people.phone;
                char tem2[100];
                sprintf(tem2,"%.2lf",now->AMOUNT);
                testData[i][6] = newString(tem2);
                //testData[i][6] = newString(itoa((int)now->AMOUNT,ch2,10));
                i++;
        };
    int columnWidth[] = {24, 8, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 7);
    for (int j = 0; j < num; j++) Table_pushLine(dataTable, testData[j]);
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Enter键以返回..."));
    UI_startScene(SCENE_TOTAL_GIFT, STR_BUF("礼物总情况"));
}

void TotalGift_inLoop(){
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键返回
            UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
            UI_endScene();
        }
    }
}

int TotalGift_render(int line){
    Table_render(dataTable, line);
}