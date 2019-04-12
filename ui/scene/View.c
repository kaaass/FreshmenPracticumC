//
// Created by guyis on 2019/4/11.
//

#include "View.h"
#include "../UI.h"
#include "../Table.h"

#define TABLE_COLUNN_NUM 5

Table *dataTable;

void View_init() {
    stringbuf columnName[] = {
            STR_BUF("测试"),
            STR_BUF("列A"),
            STR_BUF("列B"),
            STR_BUF("列C"),
            STR_BUF("列D")
    };
    stringbuf testData[][TABLE_COLUNN_NUM] = {
            {STR_BUF("1"), STR_BUF("测试"), STR_BUF("测试"), STR_BUF("66666"), STR_BUF("测试")},
            {STR_BUF("2"), STR_BUF("哈哈哈哈"), STR_BUF("longlonglonglonglonglong"), STR_BUF("我很长我很长我很长我很长"), STR_BUF("测试")},
            {STR_BUF("3"), STR_BUF("测试"), STR_BUF("233333"), STR_BUF("测试"), STR_BUF("测试")},
            {STR_BUF("4"), STR_BUF("你写"), STR_BUF("代码"), STR_BUF("像"), STR_BUF("蔡徐坤")},
            {STR_BUF("5"), STR_BUF("这表格"), STR_BUF("写的"), STR_BUF("累死"), STR_BUF("我了")}
    };
    int columnWidth[] = {10, 21, 21, 21, 21};
    READ_SPEC = true;
    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
    Table_setColumnTitle(dataTable, columnName, columnWidth, TABLE_COLUNN_NUM);
    for (int i = 0; i < 5; i++) Table_pushLine(dataTable, testData[i]);
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