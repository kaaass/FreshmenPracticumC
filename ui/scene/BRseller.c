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
#include "BRseller.h"
#include "../../model/Consultation.h"

Menu *sellerMenu;

Table *dataTable;
void BRseller_init(){
    int num = 0, i = 0;
    ForEach(cur,SELLING_RECORD){num++;}
    stringbuf sellers_name[num];
    ForEach(cur,PROVIDER){
        Provider *record = GetData(Provider,cur);
        sellers_name[i] = record->name;
        i++;
    }
    stringbuf columnName[] = {
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF("")
    };
    sellerMenu = Menu_create(-1, 3, sellers_name, num, 0);
    UI_startScene(SCENE_BRSELLER, STR_BUF("查询供货商"));
    int columnWidth[] = {24, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
}

void BRseller_inLoop(){
    Menu_inLoop(sellerMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ENTER){
            Database *create = Supplier(sellerMenu->cur);
            int i=0,num=0;
            ForEach(cur, create){num++;}
            stringbuf testData[num][6];
            ForEach(cur, create){
                PurchaseRecord *now = GetData(PurchaseRecord, cur);
                Mountings *rec_mountings = GetById(Mountings,MOUNTINGS,now->partId);
                char ch1[20],ch2[20],ch3[20],ch4[20],ch5[20];
                sprintf(ch1, "%d", now->id);
                testData[i][0] = newString(ch1);
                testData[i][1] = rec_mountings->name;
                sprintf(ch2,"%d",now->amount);
                testData[i][2] = newString(ch2);
                sprintf(ch3, "%d", now->amount);
                testData[i][3] = newString(ch3);
                sprintf(ch4, "%f", now->total);
                testData[i][4] = newString(ch4);
                sprintf(ch5, "%f", now->price);
                i++;
            };
            int columnWidth[] = {24, 8, 8, 19, 13, 9};
            dataTable = Table_create(-1, 1, 100, 8, 1, 0);
            stringbuf columnName[] = {
                    STR_BUF("Id"),
                    STR_BUF("零配件"),
                    STR_BUF("数量"),
                    STR_BUF("总价"),
                    STR_BUF("单价"),
            };
            Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
            for (int j = 0; j < num; j++)
                Table_pushLine(dataTable, testData[j]);
        }
    }
}

int BRseller_render(int line){
    UI_printMidString(LITERAL("请选择供货商："), line);
    line += 1;
    putchar('\n');
    line += 1;
    line += Menu_render(sellerMenu, line);
    return line;
}