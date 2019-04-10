//
// Created by guyis on 2019/4/8.
//

#include <assert.h>
#include <stdio.h>
#include "Menu.h"
#include "../util/MemoryUtil.h"
#include "UI.h"
#include "UI_Utils.h"

/**
 * 创建菜单
 * @param name
 * @param num
 * @param def
 * @param toggle
 * @return
 */
Menu *Menu_create(int x, int y, string name[], int num, int def) {
    Menu *menu = MALLOC(Menu);
    menu->x = x;
    menu->y = y;
    menu->num = num;
    menu->cur = def;
    memcpy(menu->name, name, sizeof(string) * num);
    return menu;
}

void Menu_renderToggle(Menu *menu, int line) {
    Position cur;
    Position org = UI_getCursorPos();
    cur.x = menu->x + 2;
    cur.y = line + menu->y;
    for (int i = 0; i < menu->num; ++i) {
        UI_moveCursor(cur);
        if (menu->cur == i) {
            putchar('*');
        } else {
            putchar(' ');
        }
        cur.y++;
    }
    UI_moveCursor(org);
}

/**
 * 输出菜单内容
 * @param menu
 * @return 占用行数
 */
int Menu_render(Menu *menu, int line) {
    menu->line = line;
    Position pos = { .x = menu->x, .y = menu->y + line };
    for (int i = 0; i < menu->num; ++i) {
        UI_moveCursor(pos);
        printf("[   ] %s\n", CSTR(menu->name[i]));
        pos.y++;
    }
    Menu_renderToggle(menu, line);
    return menu->num + menu->y;
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
                Menu_renderToggle(menu, menu->line);
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                menu->cur++;
                if (menu->cur >= menu->num)
                    menu->cur = 0;
                Menu_renderToggle(menu, menu->line);
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
    }
    free(menu);
}