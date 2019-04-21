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
#include "../../model/Forecase.h"
#include "../../data/TableProvider.h"

Table *dataTable;

void Inventory_init() {
    /*
     * 初始化表格
     */
    stringbuf columnName[] = {
            STR_BUF("种类"),
            STR_BUF("名称"),
            STR_BUF("库存"),
            STR_BUF("最近进货价格"),
            STR_BUF("预测进货价格")
    };
    int columnWidth[] = {10, 25, 10, 15, 15};
    dataTable = Table_create(-1, 1, 81, 25, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 5);
    /*
     * 初始化数据
     */
    stringbuf testData[5];
    time_t nowTime = time(NULL);
    ForEach(cur, MOUNTINGS) {
        Mountings *now = GetData(Mountings, cur);
        Provider *provider = GetById(Provider, PROVIDER, now->sellerId);

        testData[0] = Mountings_getTypeString(now->type);
        testData[1] = concat(4, now->name, LITERAL(" ("), provider->name, LITERAL(")")),
        testData[2] = toIntString(now->amount);
        testData[3] = toRmbString(now->price);
        testData[4] = toRmbString(forecasePurchasePrice(nowTime, now->id));
        Table_pushLine(dataTable, testData);
    }
    //
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
    UI_startScene(SCENE_INVENTORY, STR_BUF("库存"));
}

void Inventory_inLoop() {
    Table_inLoop(dataTable);
    UI_setFooterUpdate(concat(2, LITERAL("按ESC键返回上一页。当前选中："), Table_getSelection(dataTable)));
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

int Inventory_render(int line) {
    Table_render(dataTable, line);
}