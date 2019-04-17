//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_MENU_H
#define FRESHMAN_PROJ_C_MENU_H

#include "../util/StringUtil.h"
#define _MAX_MENU_ITEM 10

typedef struct {
    int x;
    int y;
    int num;
    int cur;
    int line;
    string name[_MAX_MENU_ITEM];
} Menu;

Menu *Menu_create(int x, int y, string name[], int num, int def);

int Menu_render(Menu *menu, int line);

void Menu_inLoop(Menu *);

void Menu_setItemText(Menu *, int, stringbuf);

void Menu_setCur(Menu *, int cur);

void Menu_setCurAndUpdate(Menu *, int cur);

void Menu_destroy(Menu *);

#endif //FRESHMAN_PROJ_C_MENU_H
