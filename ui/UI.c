//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "UI_Utils.h"
#include "UI.h"
#include "scene/Welcome.h"

#define COLOR_DEF 0x70
#define COLOR_FOOTER 0x07

List *BREAD_CRUMB;
stringbuf FOOTER;
int NOW_SCENE;
bool READ_SPEC;
int SPEC_KEY = 0;

void UI_init() {
    BREAD_CRUMB = Create(string);
    FOOTER = $init$;
    // 默认场景
    Welcome_init();
}

void UI_mainLoop() {
    UI_init();
    UI_render();
    while (true) {
        UI_setCursorVisible(!READ_SPEC);
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

int UI_renderBreadCrumb() {
    ForEach(cur, BREAD_CRUMB) {
        printf(" %s > ", CSTR(*GetData(string, cur)));
    }
    putchar('\n');
    for (int i = 0; i < CON_WIDTH; i++) putchar('-');
    return 2;
}

int UI_renderScene(int line) {
    switch (NOW_SCENE) {
        case SCENE_WELCOME:
            return Welcome_render(line);
        default:
            return 0;
    }
}

int UI_renderFooter() {
    UI_setTextColor(COLOR_FOOTER);
    UI_moveCursor((Position) {0, CON_HEIGHT - 1});
    printf("%s", CSTR(FOOTER));
    UI_setTextColor(COLOR_DEF);
    Position org = UI_getCursorPos();
    int clearCnt = (int) (CON_WIDTH - FOOTER->unitCnt);
    while (clearCnt--) putchar(' ');
    UI_moveCursor(org);
    return 1;
}

void UI_render() {
    int lineCnt = 0;
    // 重绘
    system("cls");
    // 面包屑
    lineCnt += UI_renderBreadCrumb();
    // 场景
    UI_renderScene(lineCnt);
    // 页脚
    UI_renderFooter();
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

/**
 * 设置页脚
 * @param footer 传入字面字符串常量
 */
void UI_setFooterUpdate(string footer) {
    freeAssign(&FOOTER, cloneString(footer));
    UI_renderFooter();
}

void BreadCrumb_enter(string name) {
    // 更新标题
    stringbuf title = concat(2, name, LITERAL(" - 进销存系统 v1.0"));
    UI_setTitle(title);
    $STR_BUF(title);
    // 插入面包屑
    Database_pushBack(BREAD_CRUMB, Data(string, &name));
}

void BreadCrumb_exit() {
    Database_pop(BREAD_CRUMB);
}