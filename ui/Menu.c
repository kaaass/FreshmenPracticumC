//
// Created by guyis on 2019/4/8.
//

#include <assert.h>
#include <stdio.h>
#include "Menu.h"
#include "../util/MemoryUtil.h"
#include "UI.h"

/**
 * 创建菜单
 * @param name
 * @param num
 * @param def
 * @param toggle
 * @return
 */
Menu *Menu_create(string name[], int num, int def, string toggle[]) {
    Menu *menu = MALLOC(Menu);
    menu->num = num;
    menu->cur = def;
    for (int i = 0; i < num; ++i) {
        if (toggle == NULL) {
            menu->name[i] = concat(2, LITERAL("[   ] "), name[i]);
            menu->toggle[i] = concat(2, LITERAL("[ * ] "), name[i]);
        } else {
            menu->name[i] = name[i];
            menu->toggle[i] = toggle[i];
        }
    }
    return menu;
}

/**
 * 输出菜单内容
 * @param menu
 * @return 占用行数
 */
int Menu_render(Menu *menu) {
    for (int i = 0; i < menu->num; ++i) {
        if (menu->cur == i) {
            printf("%s\n", CSTR(menu->toggle[i]));
        } else {
            printf("%s\n", CSTR(menu->name[i]));
        }
    }
    return menu->num;
}

/**
 * 菜单的循环间事件
 * @param menu
 */
void Menu_inLoop(Menu *menu) {
    if (READ_SPEC) {
        switch (SPEC_KEY) {
            case KEY_UP:
            case KEY_PGUP:
                menu->cur--;
                if (menu->cur < 0)
                    menu->cur = menu->num - 1;
                UI_render();
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                menu->cur++;
                if (menu->cur >= menu->num)
                    menu->cur = 0;
                UI_render();
                break;
            default:
                break;
        }
    }
}

/**
 * 设置菜单当前显示的项目
 * @param menu
 * @param cur 当前显示项目，0开始，若等于num则无选择项目
 */
void Menu_setCur(Menu *menu, int cur) {
    menu->cur = cur;
}

/**
 * 设置菜单当前显示的项目并直接更新显示
 * @param menu
 * @param cur
 */
void Menu_setCurAndUpdate(Menu *menu, int cur) {
    Menu_setCur(menu, cur);
    UI_render();
}

/**
 * 销毁菜单
 * @param menu
 */
void Menu_destroy(Menu *menu) {
    assert(menu);
    for (int i = 0; i < menu->num; ++i) {
        $STR_BUF(menu->name[i]);
        $STR_BUF(menu->toggle[i]);
    }
    free(menu);
}