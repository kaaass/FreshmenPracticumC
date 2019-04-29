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
#include "../../data/TableProvider.h"

Table *dataTable;

void TotalGift_init() {
    /*
     * 初始化表格
     */
    stringbuf columnName[] = {
            STR_BUF("时间"),
            STR_BUF("种类"),
            STR_BUF("名称"),
            STR_BUF("数量"),
            STR_BUF("客户"),
            STR_BUF("联系方式"),
            STR_BUF("价值")
    };
    int columnWidth[] = {17, 8, 23, 6, 10, 13, 15};
    dataTable = Table_create(-1, 1, 100, 25, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, 7);
    /*
     * 初始化表格数据
     */
    Database *create = sort_gift();
    stringbuf testData[7];
    ForEach(cur, create) {
        Present_Situation *now = GetData(Present_Situation, cur);
        Mountings *rec_mountings = GetById(Mountings, MOUNTINGS, now->partId);
        Provider *provider = GetById(Provider, PROVIDER, rec_mountings->sellerId);

        testData[0] = Time_toLocalString(now->time_recording);
        testData[1] = typename(now->partId);
        testData[2] = concat(4, rec_mountings->name, LITERAL(" ("), provider->name, LITERAL(")")),
        testData[3] = toIntString(now->amount);
        testData[4] = now->people.name;
        testData[5] = now->people.phone;
        testData[6] = toRmbString(now->AMOUNT);
        Table_pushLine(dataTable, testData);
    }
    //
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
    UI_startScene(SCENE_TOTAL_GIFT, STR_BUF("礼物赠送记录"));
}

void TotalGift_inLoop() {
    Table_inLoop(dataTable);
    UI_setFooterUpdate(concat(2, LITERAL("按ESC键返回上一页。当前选中："), Table_getSelection(dataTable)));
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

int TotalGift_render(int line) {
    Table_render(dataTable, line);
}