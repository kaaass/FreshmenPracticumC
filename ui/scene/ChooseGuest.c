//
// Created by guyis on 2019/4/14.
//

#include <assert.h>
#include "ChooseGuest.h"
#include "../../data/TableGuest.h"
#include "../UI.h"
#include "../Menu.h"
#include "../../data/DataManager.h"
#include "../Table.h"
#include "../UI_Utils.h"
#include "../../model/Insert.h"
#include "../../data/TableProvider.h"

int curView = 1, curType;
Guest CUR_GUEST = {.id = -1}, tempGuest;
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
        if (type == 0) { // 客户
            CUR_GUEST = *GetById(Guest, GUEST, guestId);
        } else { // 供应商
            Provider *data = GetById(Provider, PROVIDER, guestId);
            CUR_GUEST.name = cloneString(data->name);
            CUR_GUEST.phone = cloneString(data->phone);
        }
    } else {
        CUR_GUEST.name = STR_BUF("尚未选择");
        CUR_GUEST.phone = STR_BUF("NaN");
    }
    curView = 1;
    curType = type;
    tempGuest.id = -1;
    tempGuest.name = $init$;
    tempGuest.phone = $init$;
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

void updateMenuText() {
    freeAssign(&createGuestMenu->name[0], concat(2, LITERAL("姓名："), tempGuest.name));
    freeAssign(&createGuestMenu->name[1], concat(2, LITERAL("电话："), tempGuest.phone));
    // freeAssign(&selGuestMenu->name[0], concat(2, LITERAL("选择现有："), CUR_GUEST.name));
}

void updateGuestTable() {
    Table_clear(guestList);
    stringbuf line[2];
    if (curType == 0) {
        // 客户
        ForEach(cur, GUEST) {
            Guest *data = GetData(Guest, cur);
            line[0] = cloneString(data->name);
            line[1] = cloneString(data->phone);
            Table_pushLine(guestList, line);
        }
    } else {
        // 供货商
        ForEach(cur, PROVIDER) {
            Provider *data = GetData(Provider, cur);
            line[0] = cloneString(data->name);
            line[1] = cloneString(data->phone);
            Table_pushLine(guestList, line);
        }
    }
    Table_setCurAndUpdate(guestList, CUR_GUEST.id == -1 ? 1: CUR_GUEST.id);
}

void ChooseGuest_inLoopMain() {
    Menu_inLoop(selGuestMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        } else if (SPEC_KEY == KEY_ENTER) {
            switch (selGuestMenu->cur) {
                case 0:
                    updateGuestTable();
                    // 跳转
                    curView = 2;
                    UI_render();
                    break;
                case 1:
                    tempGuest.id = -1;
                    freeAssign(&tempGuest.name, $init$);
                    freeAssign(&tempGuest.phone, $init$);
                    // 跳转
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
        } else if (SPEC_KEY == KEY_ENTER) {
            assert(guestList->cur > 0);
            if (curType == 0) { // 客户
                Guest *data = GetById(Guest, GUEST, guestList->cur);
                CUR_GUEST.name = cloneString(data->name);
                CUR_GUEST.phone = cloneString(data->phone);
            } else { // 供应商
                Provider *data = GetById(Provider, PROVIDER, guestList->cur);
                CUR_GUEST.name = cloneString(data->name);
                CUR_GUEST.phone = cloneString(data->phone);
            }
            CUR_GUEST.id = guestList->cur;
            UI_endScene();
        }
    }
}

void addToDatabase() {
    int id;
    CUR_GUEST = tempGuest;
    if (curType == 0) { // 客户
        if ((id = Insert_hasGuest(CUR_GUEST.name, CUR_GUEST.phone)) != 0) {
            CUR_GUEST.id = id;
            return;
        }
        Insert_guest(CUR_GUEST.name, CUR_GUEST.phone);
        CUR_GUEST.id = Database_size(GUEST);
    } else { // 供货商
        if ((id = Insert_hasProvider(CUR_GUEST.name, CUR_GUEST.phone)) != 0) {
            CUR_GUEST.id = id;
            return;
        }
        Insert_provider(CUR_GUEST.name, CUR_GUEST.phone);
        CUR_GUEST.id = Database_size(PROVIDER);
    }
}

void ChooseGuest_inLoopCreate() {
    Menu_inLoop(createGuestMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (createGuestMenu->cur) {
                case 0: // 输入名称
                    UI_setFooterUpdate(LITERAL("请输入名称："));
                    UI_setCursorVisible(true);
                    freeAssign(&tempGuest.name, readLine());
                    updateMenuText();
                    UI_render();
                    break;
                case 1: // 输入电话
                    UI_setFooterUpdate(LITERAL("请输入电话："));
                    UI_setCursorVisible(true);
                    freeAssign(&tempGuest.phone, readLine());
                    updateMenuText();
                    UI_render();
                    break;
                case 2: // 添加
                    // 校验
                    if (length(tempGuest.name) < 1) {
                        UI_setFooterUpdate(LITERAL("姓名不能为空！"));
                        return;
                    }
                    if (length(tempGuest.phone) < 1) {
                        UI_setFooterUpdate(LITERAL("电话不能为空！"));
                        return;
                    }
                    // 逻辑
                    addToDatabase();
                    UI_endScene();
                    break;
                case 3: // 取消并返回
                    curView = 1;
                    UI_render();
                    break;
            }
        }
    }
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

Guest ChooseGuest_result() {
    Guest ret = CUR_GUEST;
    CUR_GUEST.id = -1;
    CUR_GUEST.name = $init$;
    CUR_GUEST.phone = $init$;
    return ret;
}
