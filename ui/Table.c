//
// Created by guyis on 2019/4/11.
//

#include <stdio.h>
#include "Table.h"
#include "../util/MemoryUtil.h"
#include "UI.h"
#include "UI_Utils.h"

#define COLOR_SELECTION 0x07

void Table_renderToggle(Table *table, int line, int orgCur);

/**
 * 创建表格控件
 * @param x 左上角x轴坐标
 * @param y 左上角y轴坐标
 * @param w 宽度
 * @param h 高度
 * @param def 默认选中项
 * @return
 */
Table *Table_create(int x, int y, int w, int h, int def) {
    Table *table = MALLOC(Table);
    if (x < 0) {
        // 自动居中
        table->x = (CON_WIDTH - w) / 2;
    } else {
        table->x = x;
    }
    table->y = y;
    table->width = w;
    table->height = h;
    table->cur = def;
    table->columns = Create(TableLine);
    table->top = 1;
    return table;
}

/**
 * 设置表头信息
 * @param table 表格控件
 * @param columnName 标题
 * @param columnWidth 该列宽度
 * @param columnNum 列数量
 */
void Table_setColumnTitle(Table *table, stringbuf *columnName, int *columnWidth, int columnNum) {
    memcpy(table->columnName, columnName, sizeof(stringbuf) * columnNum);
    memcpy(table->columnWidth, columnWidth, sizeof(int) * columnNum);
    table->columnNum = columnNum;
}

int mid(int w, int outW) {
    return (outW - w) / 2;
}

void printBound(Table *table) {
    for (int i = 0; i < table->columnNum; i++) {
        putchar('+');
        for (int j = 0; j < table->columnWidth[i]; j++) putchar('-');
    }
    putchar('+');
}

char *processString(stringbuf str, int maxLen) {
    char* buf = CSTR(str);
    int curLen;
    // 未超过限制
    if (strlen(buf) <= maxLen) return buf;
    // 超过
    for (int i = 0; i < strlen(buf); i++) {
        curLen = buf[i] > 0x7F ? 2: 1;
        if (maxLen - curLen - i + 1 <= 3) {
            buf[i] = '.';  buf[i+1] = '.';  buf[i+2] = '.';  buf[i+3] = '\0';
            break;
        }
        if (buf[i] > 0x7F) {
            i++;
            continue;
        }
    }
    return buf;
}

void printLine(Table *table, stringbuf content[]) {
    for (int i = 0; i < table->columnNum; i++) {
        char *buf = processString(content[i], table->columnWidth[i]);
        int len = (int) strlen(buf);
        putchar('|');
        UI_blanks(mid(len, table->columnWidth[i]));
        printf("%s", buf);
        UI_blanks(table->columnWidth[i] - len - mid(len, table->columnWidth[i]));
    }
    putchar('|');
}

/**
 * 渲染表格
 * @param table 表格控件
 * @param line 内容区开始行
 * @return
 */
int Table_render(Table *table, int line) {
    int itemNum = (int) Database_size(table->columns),
        usedLine = 4;
    table->line = line;
    Position pos = { .x = table->x, .y = table->y + line };
    /*
     * 表头
     */
    // 边框
    UI_moveCursor(pos);
    printBound(table); pos.y++;
    // 标题
    UI_moveCursor(pos);
    printLine(table, table->columnName); pos.y++;
    // 边框
    UI_moveCursor(pos);
    printBound(table); pos.y++; // 边框
    // 打印表内容
    UI_moveCursor(pos);
    ForEach(cur, table->columns) {
        TableLine *data = GetData(TableLine, cur);
        if (data->id < table->top) continue;
        if (usedLine >= table->height) break;
        // 打印一行
        if (data->id == table->cur) {
            Table_renderToggle(table, line, -1); pos.y++;
        } else {
            UI_moveCursor(pos);
            printLine(table, data->content); pos.y++;
        }
        usedLine++;
    }
    UI_moveCursor(pos);
    printBound(table); // 边框
    return usedLine;
}

void Table_renderToggle(Table *table, int line, int orgCur) {
    Position pos = { .x = table->x, .y = table->y + line };
    if (orgCur >= 0) { // orgCur应位于表内
        TableLine *data = GetById(TableLine, table->columns, orgCur);
        pos.y = table->y + line + 3 + orgCur - table->top;
        UI_moveCursor(pos);
        printLine(table, data->content);
    }
    UI_setTextColor(COLOR_SELECTION);
    TableLine *data = GetById(TableLine, table->columns, table->cur);
    pos.y = table->y + line + 3 + table->cur - table->top;
    UI_moveCursor(pos);
    printLine(table, data->content);
    UI_setTextColor(COLOR_DEF);
}

/**
 * 表格循环间事件
 * @param table 表格控件
 */
void Table_inLoop(Table *table) {
    int lstCur = table->cur;
    if (READ_SPEC) {
        switch (SPEC_KEY) {
            case KEY_UP:
            case KEY_PGUP:
                table->cur--;
                if (table->cur < 1)
                    table->cur = (int) Database_size(table->columns);
                Table_renderToggle(table, table->line, lstCur);
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                table->cur++;
                if (table->cur > (int) Database_size(table->columns))
                    table->cur = 1;
                Table_renderToggle(table, table->line, lstCur);
                break;
            default:
                break;
        }
    }
}

/**
 * 向表格插入一行数据
 * @param table 表格控件
 * @param line 加入行数据
 */
void Table_pushLine(Table *table, stringbuf *line) {
    TableLine tableLine = {
            .num = table->columnNum
    };
    memcpy(&tableLine.content, line, sizeof(stringbuf) * table->columnNum);
    Database_pushBack(table->columns, Data(TableLine, &tableLine));
}

/**
 * 清空表格数据
 * @param table 表格控件
 */
void Table_clear(Table *table) {
    Database_clear(table->columns);
}

/**
 * 设置当前选择项
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table_setCur(Table *table, int cur) {
    table->cur = cur;
}

/**
 * 设置当前选择项并更新
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table_setCurAndUpdate(Table *table, int cur) {
    Table_setCur(table, cur);
    UI_render();
}

/**
 * 销毁表格控件
 * @param table 表格控件
 */
void Table_destroy(Table *table) {
    // TODO: 完成销毁表格控件
}