//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include <conio.h>
#include "UI.h"
#include "scene/Welcome.h"

string TITLE;
List *BREAD_CRUMB;
int NOW_SCENE;
bool READ_SPEC;
int SPEC_KEY = 0;

void UI_init() {
    BREAD_CRUMB = Create(string);
    // 默认场景
    Welcome_init();
}

void UI_mainLoop() {
    UI_init();
    UI_render();
    while (true) {
        UI_getSpecKey();
        switch (NOW_SCENE) {
            case SCENE_WELCOME:
                Welcome_inLoop();
                break;
            default:
                return;
        }
    }
}

int UI_renderHead() {
    stringbuf titleLine = concat(3, LITERAL("----- "), TITLE, LITERAL(" -----"));
    stringbuf midLine = UI_midString(titleLine);
    printf("%s\n", CSTR(midLine));
    $STR_BUF(titleLine);
    $STR_BUF(midLine);
    return 1;
}

int UI_renderBreadCrumb() {
    printf("%s\n", CSTR(LITERAL("首页 > 还没写 > 咕")));
    return 1;
}

int UI_renderScene() {
    switch (NOW_SCENE) {
        case SCENE_WELCOME:
            return Welcome_render();
        default:
            return 0;
    }
}

int UI_renderFooter() {
    printf("%s\n", CSTR(LITERAL("请输入：还没写，咕")));
    return 1;
}

void UI_render() {
    int lineCnt = 0;
    // 重绘
    system("cls");
    // 标题
    lineCnt += UI_renderHead();
    // 面包屑
    lineCnt += UI_renderBreadCrumb();
    // 场景
    lineCnt += UI_renderScene();
    // 占位行
    int blanks = CON_HEIGHT - lineCnt - 2;
    while (blanks--) printf("\n");
    // 页脚
    UI_renderFooter();
}

/**
 * 返回居中字符串
 * @param str
 * @return
 */
stringbuf UI_midString(stringbuf str) {
    size_t blanks = ((CON_WIDTH - str->unitCnt) / 2);
    return concat(2, repeat(LITERAL(" "), blanks), str);
}

/**
 * 读取特殊键键值
 * @return
 */
void UI_getSpecKey() {
    if (READ_SPEC) {
        int key = getch();
        if (key == KEY_SIG) {
            SPEC_KEY = getch();
        } else {
            if (key == KEY_ENTER) {
                SPEC_KEY = KEY_ENTER;
            } else {
                SPEC_KEY = 0;
            }
        }
    }
}

void BreadCrumb_enter(string name) {
    Database_pushBack(BREAD_CRUMB, Data(string, &name));
}

void BreadCrumb_exit() {
    Database_pop(BREAD_CRUMB);
}