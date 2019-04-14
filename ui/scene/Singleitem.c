//
// Created by hasee on 2019/4/13.
//
#include "Singleitem.h"
#include <stdio.h>
#include "Welcome.h"
#include "../UI.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "Items.h"

Menu *singleMenu;

void Singleitem_init(){
    READ_SPEC = true;//是否读入上下左右键，读入字符串就要false
    stringbuf name[] = {
            STR_BUF("    鼠标"),
            STR_BUF("    键盘"),
            STR_BUF("    内存"),
            STR_BUF("    显卡"),
            STR_BUF("    硬盘"),
            STR_BUF("    CPU"),
            STR_BUF("    显示器")
    };
    singleMenu = Menu_create(-1, 4, name, 7, 0);
    UI_startScene(SCENE_SINGLEITEM, STR_BUF("单个浏览"));
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
}

void Singleitem_inLoop(){
    Menu_inLoop(singleMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ESC){
            UI_endScene();
        }
        if (SPEC_KEY == KEY_ENTER){
            Items_init(singleMenu->cur);
            }
        }
}

int Singleitem_render(int line){
    UI_printMidString(LITERAL("单个浏览"), line++);
    putchar('\n'); line += 1;
    line += Menu_render(singleMenu, line);
    return line;
}