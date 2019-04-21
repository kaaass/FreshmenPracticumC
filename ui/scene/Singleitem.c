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
#include "../../data/TableProvider.h"

Table *dataTable;

void Singleitem_init() {
    /*
     * 初始化表格
     */
    stringbuf columnName[] = {
            STR_BUF("种类"),
            STR_BUF("名称"),
            STR_BUF("总价值"),
            STR_BUF("数量"),
            STR_BUF("库存")
    };
    int columnWidth[] = {10, 25, 15, 10, 10};
    dataTable = Table_create(-1, 1, 76, 25, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 5);
    /*
     * 初始化数据
     */
    Database *create = Search_amount_gift();
    stringbuf testData[5];
    ForEach(cur, create) {
        SingleGift *now = GetData(SingleGift, cur);
        Mountings *mountings = GetById(Mountings, MOUNTINGS, now->partId);
        Provider *provider = GetById(Provider, PROVIDER, mountings->sellerId);
        testData[0] = Mountings_getTypeString(now->type);
        testData[1] = concat(4, mountings->name, LITERAL(" ("), provider->name, LITERAL(")")),
        testData[2] = toRmbString(now->total);
        testData[3] = toIntString(now->amount);
        testData[4] = toIntString(mountings->amount);
        Table_pushLine(dataTable, testData);
    }
    //
    READ_SPEC = true;
    UI_startScene(SCENE_SINGLEITEM, STR_BUF("礼物情况统计"));
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
}

void Singleitem_inLoop() {
    Table_inLoop(dataTable);
    UI_setFooterUpdate(concat(2, LITERAL("按ESC键返回上一页。当前选中："), Table_getSelection(dataTable)));
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

int Singleitem_render(int line) {
    Table_render(dataTable, line);
}