//
// Created by guyis on 2019/4/14.
//

#include "ChooseGuest.h"
#include "../../data/TableGuest.h"
#include "../UI.h"
#include "../Menu.h"
#include "../../data/DataManager.h"
#include "../Table.h"

int GUEST_ID = -1, curView = 1;
Guest CUR_GUEST = {.id = -1};
Menu *selGuestMenu;
Menu *createGuestMenu;
Table *guestList;

#define MENU_SEL_GUEST_CNT 2
#define MENU_CREATE_GUEST_CNT 4
#define TABLE_COLUNN_NUM 2

/**
 * 初始化选择客户视图
 * @param guestId
 * @param type 0 - 客户 1 - 供货商
 */
void ChooseGuest_init(int guestId, int type) {
    READ_SPEC = true;
    /*
     * 初始化数据
     */
    if (guestId > 0) {
        CUR_GUEST = *GetById(Guest, GUEST, guestId);
    } else {
        CUR_GUEST.name = STR_BUF("尚未选择");
        CUR_GUEST.phone = STR_BUF("NaN");
    }
    curView = 1;
    /*
     * 初始化菜单
     */
    stringbuf name[] = {
        concat(2, LITERAL("选择现有："), CUR_GUEST.name),
        type == 0 ? STR_BUF("增加客户"): STR_BUF("增加供货商")
    };
    selGuestMenu = Menu_create(-1, 10, name, MENU_SEL_GUEST_CNT, 0);
    stringbuf nameCreate[] = {
            STR_BUF("姓名："),
            STR_BUF("电话号码："),
            STR_BUF("添加"),
            STR_BUF("取消")
    };
    createGuestMenu = Menu_create(45, 10, nameCreate, MENU_CREATE_GUEST_CNT, 0);
    /*
     * 初始化表格
     */
    stringbuf columnName[] = {
            STR_BUF("姓名"),
            STR_BUF("电话")
    };
    int columnWidth[] = {20, 20};
    guestList = Table_create(-1, 1, 43, 20, 1, -1);
    Table_setColumnTitle(guestList, columnName, columnWidth, TABLE_COLUNN_NUM);
    //
    UI_setFooterUpdate(LITERAL(""));
    UI_startScene(SCENE_CHOOSE_GUEST, type == 0 ? STR_BUF("选择客户"): STR_BUF("选择供货商"));
}

void ChooseGuest_inLoopMain() {
    Menu_inLoop(selGuestMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        } else if (SPEC_KEY == KEY_ENTER) {
            switch (selGuestMenu->cur) {
                case 0:
                    curView = 2;
                    UI_render();
                    break;
                case 1:
                    curView = 3;
                    UI_render();
                    break;
                default:
                    break;
            }
        }
    }
}

void ChooseGuest_inLoopSelect() {
    Table_inLoop(guestList);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            curView = 1;
            UI_render();
        }
    }
}

void ChooseGuest_inLoopCreate() {
    Menu_inLoop(createGuestMenu);
}

int ChooseGuest_renderMain(int line) {
    Menu_render(selGuestMenu, line);
    return line;
}

int ChooseGuest_renderSelect(int line) {
    Table_render(guestList, line);
    return line;
}

int ChooseGuest_renderCreate(int line) {
    Menu_render(createGuestMenu, line);
    return line;
}

void ChooseGuest_inLoop() {
    switch (curView) {
        case 2: // 选择
            return ChooseGuest_inLoopSelect();
        case 3: // 创建
            return ChooseGuest_inLoopCreate();
        case 1: // 主选单
        default:
            return ChooseGuest_inLoopMain();
    }
}

int ChooseGuest_render(int line) {
    switch (curView) {
        case 2: // 选择
            UI_setFooterUpdate(LITERAL("单击Enter键以选择，Esc以返回"));
            break;
        case 3: // 创建
            UI_setFooterUpdate(LITERAL("单击Enter键以输入"));
            break;
        case 1: // 主选单
        default:
            UI_setFooterUpdate(LITERAL(""));
            break;
    }
    switch (curView) {
        case 2: // 选择
            return ChooseGuest_renderSelect(line);
        case 3: // 创建
            return ChooseGuest_renderCreate(line);
        case 1: // 主选单
        default:
            return ChooseGuest_renderMain(line);
    }
}
