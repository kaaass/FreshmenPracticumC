//
// Created by guyis on 2019/4/11.
//

#include "View.h"
#include "../UI.h"
#include "../Table.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "ViewSell.h"
#include "ViewPurchase.h"

#define MENU_ITEM_CNT 2

Menu *selTypeMenu;

void View_init() {
    stringbuf menuName[] = {
            STR_BUF("  进货记录"),
            STR_BUF("  销售记录")
    };
    selTypeMenu = Menu_create(-1, 4, menuName, MENU_ITEM_CNT, 0);
    UI_startScene(SCENE_VIEW, STR_BUF("浏览记录"));
}

void View_inLoop() {
    Menu_inLoop(selTypeMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (selTypeMenu->cur) {
                case 0:
                    ViewPurchase_init();
                    break;
                case 1:
                    ViewSell_init();
                    break;
            }
        } else if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

int View_render(int line) {
    line += 7;
    UI_printMidString(LITERAL("请选择要查看的记录类型："), line++);
    Menu_render(selTypeMenu, line);
    UI_setFooterUpdate(LITERAL("按Enter以选择，Esc以返回"));
}