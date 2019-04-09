//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_MENU_H
#define FRESHMAN_PROJ_C_MENU_H

#include "../util/StringUtil.h"
#define _MAX_MENU_ITEM 10

typedef struct {
    int num;
    int cur;
    string name[_MAX_MENU_ITEM];
    string toggle[_MAX_MENU_ITEM];
} Menu;

Menu *Menu_create(string name[], int num, int def, string toggle[]);

int Menu_render(Menu *);

void Menu_inLoop(Menu *);

void Menu_setCur(Menu *, int cur);

void Menu_setCurAndUpdate(Menu *, int cur);

void Menu_destroy(Menu *);

#endif //FRESHMAN_PROJ_C_MENU_H
