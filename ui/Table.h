//
// Created by guyis on 2019/4/11.
//

#ifndef FRESHMAN_PROJ_C_TABLE_H
#define FRESHMAN_PROJ_C_TABLE_H

#include "../util/StringUtil.h"
#include "../core/Database.h"

#define _MAX_TABLE_COLUMN 10
#define DATA_TYPE_TableLine 10 | ID_LIKE

typedef struct {
    int id;
    stringbuf content[_MAX_TABLE_COLUMN];
    int num;
} TableLine;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int line;
    List *columns;
    stringbuf columnName[_MAX_TABLE_COLUMN];
    int columnWidth[_MAX_TABLE_COLUMN];
    int columnNum;
    int top;
    int cur;
    int columnCur;
} Table;

Table *Table_create(int x, int y, int w, int h, int def, int colDef);

void Table_setColumnTitle(Table *table, stringbuf *columnName, int *columnWidth, int columnNum);

int Table_render(Table *table, int line);

void Table_inLoop(Table *);

void Table_pushLine(Table *table, stringbuf *line);

void Table_clear(Table *table);

void Table_setCur(Table *, int cur);

void Table_setCurAndUpdate(Table *, int cur);

stringbuf Table_getSelection(Table *);

void Table_destroy(Table *);

#endif //FRESHMAN_PROJ_C_TABLE_H
