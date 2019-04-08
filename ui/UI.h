//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_UI_H
#define FRESHMAN_PROJ_C_UI_H

#include "../util/StringUtil.h"
#include "../core/Database.h"

extern string TITLE;
extern int NOW_SCENE;

void UI_mainLoop();

void UI_render();

void BreadCrumb_enter(string);

void BreadCrumb_exit();

#endif //FRESHMAN_PROJ_C_UI_H
