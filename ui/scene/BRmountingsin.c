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
#include "../../model/Consultation.h"

Menu *mountingsInMenu;

#define MENU_CNT 7

Table *dataTable;
void BRmountingsin_init(){
    stringbuf mountings_name[] = {
            STR_BUF("        鼠 标"),
            STR_BUF("        键 盘"),
            STR_BUF("        内 存"),
            STR_BUF("        显 卡"),
            STR_BUF("        硬 盘"),
            STR_BUF("         CPU"),
            STR_BUF("        屏 幕"),
    };
    stringbuf columnName[] = {
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF(""),
            STR_BUF("")
    };
    mountingsInMenu = Menu_create(-1, 3, mountings_name, MENU_CNT, 0);
    int columnWidth[] = {24, 8, 8, 19,13,9};
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
}

void BRmountingsin_inLoop(){
    Menu_inLoop(mountingsInMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ENTER){
            Database *create;
            switch(mountingsInMenu->cur){
                case 0:
                    create = AccessoryIn(0);
                    break;
                case 1:
                    create = AccessoryIn(1);
                    break;
                case 2:
                    create = AccessoryIn(2);
                    break;
                case 3:
                    create = AccessoryIn(3);
                    break;
                case 4:
                    create = AccessoryIn(4);
                    break;
                case 5:
                    create = AccessoryIn(5);
                    break;
                case 6:
                    create = AccessoryIn(6);
                    break;
                case 7:DataManager_save(LITERAL("data"));
                    exit(0);
                default:
                    break;
            }
            int i = 0, num = 0;
            ForEach(cur, create) { num++; }
            stringbuf testData[num][6];
            ForEach(cur, create) {
                PurchaseRecord *now = GetData(PurchaseRecord, cur);
                Provider *rec_provider = GetById(Provider, PROVIDER, now->sellerId);
                char ch1[20], ch2[20], ch3[20], ch4[20], ch5[20];
                sprintf(ch1, "%d", now->id);
                testData[i][0] = newString(ch1);
                testData[i][1] = rec_provider->name;
                sprintf(ch2, "%d", now->amount);
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
                    STR_BUF("供货商"),
                    STR_BUF("数量"),
                    STR_BUF("总价"),
                    STR_BUF("单价"),
            };
            Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
            for (int j = 0; j < num; j++) Table_pushLine(dataTable, testData[j]);
        }
    }
}

int BRmountingsin_render(int line){
    UI_printMidString(LITERAL("请选择配件种类："), line);
    line += 1;
    putchar('\n');
    line += 1;
    line += Menu_render(mountingsInMenu, line);
    return line;
}