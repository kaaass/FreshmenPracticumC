//
// Created by guyis on 2019/4/8.
//

#include "UI.h"
#include "scene/Welcome.h"

string TITLE;
List *BREAD_CRUMB;
int NOW_SCENE;

void UI_init() {
    BREAD_CRUMB = Create(string);
    Welcome_init();
}

void UI_mainLoop() {
    UI_init();
}

void UI_render() {

}

void BreadCrumb_enter(string name) {
    Database_pushBack(BREAD_CRUMB, Data(string, &name));
}

void BreadCrumb_exit() {
    Database_pop(BREAD_CRUMB);
}