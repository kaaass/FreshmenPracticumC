//
// Created by guyis on 2019/4/11.
//

#include "View.h"
#include "../UI.h"
#include "../Table.h"

#define SIDE_WIDTH 30
#define TABLE_WIDTH 90
#define TABLE_COLUMN_NUM 6

enum Column { // 表示当前用户在控制哪一栏
    MENU = 0, RECORD_TABLE
} curCul;

Table *dataTable;

void View_init() {
    // TODO: 此页面改为选择进货或销售记录
    /*
     * 右边栏：表格
     */
    stringbuf columnName[] = {
            STR_BUF("订单号"),
            STR_BUF("商品名"),
            STR_BUF("生产厂商"),
            STR_BUF("供货商"),
            STR_BUF("数量"),
            STR_BUF("价格"),
    };
    int columnWidth[] = {8, 16, 20, 20, 9, 10};
    READ_SPEC = true;
    dataTable = Table_create(SIDE_WIDTH, 0, TABLE_WIDTH, 27, -1, -1);
    Table_setColumnTitle(dataTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    UI_setFooterUpdate(LITERAL(""));
    UI_startScene(SCENE_VIEW, STR_BUF("浏览记录"));
}

void View_inLoop() {
    Table_inLoop(dataTable);
    UI_setFooterUpdate(Table_getSelection(dataTable));
}

int View_render(int line) {
    Table_render(dataTable, line);
}