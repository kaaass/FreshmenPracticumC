//
// Created by guyis on 2019/4/14.
//

#include "AppendOrder.h"
#include "../../data/TableOrder.h"
#include "../Menu.h"
#include "../UI.h"
#include "../UI_Utils.h"
#include "../Table.h"
#include "../../data/TableGuest.h"
#include "ChooseGuest.h"

#define MENU_CNT 3

enum OrderType CUR_TYPE;

Menu *selectMenu;
Menu *appendMenu;
Table *appendTable;
Guest curGuest;

int curCul;

#define SIDE_WIDTH 30
#define TABLE_COLUNN_NUM 5
#define TABLE_WIDTH 90
#define MENU_OP_CNT 5

void AppendOrder_init() {
    READ_SPEC = true;
    /*
     * 数据表
     */
    stringbuf columnName[] = {
            STR_BUF("配件"),
            STR_BUF("数量"),
            STR_BUF("单价"),
            STR_BUF("总价"),
            STR_BUF("时间")
    };
    int columnWidth[] = {20, 16, 16, 16, 16};
    appendTable = Table_create(SIDE_WIDTH, 0, TABLE_WIDTH, CON_HEIGHT - 4, -1, -1);
    Table_setColumnTitle(appendTable, columnName, columnWidth, TABLE_COLUNN_NUM);
    /*
     * 操作选单
     */
    stringbuf menuName[] = {
            STR_BUF("  增加记录"),
            STR_BUF("  修改选中"),
            STR_BUF("  删除选中"),
            STR_BUF("  设置对象"),
            STR_BUF("   完  成")
    };
    appendMenu = Menu_create(7, 0, menuName, MENU_OP_CNT, 0);
    /*
     * 初始化数据
     */
    curGuest.id = -1;
    curGuest.name = STR_BUF("尚未选择");
    curGuest.phone = STR_BUF("NaN");
    curCul = 0;
    UI_setFooterUpdate(LITERAL("当前为菜单，使用Tab切换至表格"));
    UI_startScene(SCENE_APPEND_ORDER, STR_BUF("新增记录"));
    SelectOrderType_init();
}

void AppendOrder_inLoop() {
    if (curCul == 0) { // 菜单
        Menu_inLoop(appendMenu);
    } else { // 表格
        Table_inLoop(appendTable);
    }
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) { // 选单切换
            if (curCul == 0) {
                curCul = 1;
                UI_setFooterUpdate(LITERAL("当前为表格，使用Tab切换至菜单"));
            } else {
                curCul = 0;
                UI_setFooterUpdate(LITERAL("当前为菜单，使用Tab切换至表格"));
            }
        } else if (SPEC_KEY == KEY_ENTER) {
            if (curCul == 0) { // 菜单下的Enter
                switch (appendMenu->cur) {
                    case 3: // 设置客户/供货商
                        ChooseGuest_init(curGuest.id, CUR_TYPE == ORDER_PURCHASE ? 1: 0);
                        break;
                    case 4: // 完成
                        // TODO: 保存逻辑
                        UI_endScene();
                        break;
                }
            }
        }
    }
}

int AppendOrder_render(int line) {
    /*
     * 右侧视图
     */
    UI_printMidStringAt(LITERAL("待存记录："), SIDE_WIDTH, 0, TABLE_WIDTH, line++);
    Table_render(appendTable, line);
    /*
     * 左侧视图
     */
    UI_printMidStringAt(LITERAL("当前订单类型"), 0, 0, 30, line++);
    switch (CUR_TYPE) {
        case ORDER_PURCHASE:
            UI_printMidStringAt(LITERAL("进货"), 0, 1, 30, line);
            break;
        case ORDER_SINGLE_BUY:
            UI_printMidStringAt(LITERAL("销售"), 0, 1, 30, line);
            break;
        case ORDER_WHOLE_SALE:
            UI_printMidStringAt(LITERAL("批发销售"), 0, 1, 30, line);
            break;
        default:
            break;
    }
    line += 5;
    if (CUR_TYPE == ORDER_PURCHASE)
        UI_printMidStringAt(LITERAL("供货商"), 0, 0, 30, line);
    else
        UI_printMidStringAt(LITERAL("客户"), 0, 0, 30, line);
    // 更新数据
    if (CUR_GUEST.id > 0 && CUR_GUEST.id != curGuest.id)
        curGuest = CUR_GUEST;
    UI_printMidStringAt(curGuest.name, 0, 2, 30, line);
    UI_printMidStringAt(curGuest.phone, 0, 3, 30, line);
    line += 7;
    Menu_render(appendMenu, line);
    return line;
}

void SelectOrderType_init() {
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    进货记录"),
            STR_BUF("    销售记录"),
            STR_BUF("    批发销售")
    };
    selectMenu = Menu_create(-1, 10, name, MENU_CNT, CUR_TYPE);
    UI_setFooterUpdate(LITERAL("按Enter键以选择"));
    UI_startScene(SCENE_SELECT_ORDER_TYPE, STR_BUF("选择订单类型"));
}

void SelectOrderType_inLoop() {
    Menu_inLoop(selectMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键选择
            CUR_TYPE = selectMenu->cur;
            UI_endScene();
        }
    }
}

int SelectOrderType_render(int line) {
    UI_printMidString(LITERAL("请选择订单类型："), line++);
    Menu_render(selectMenu, line);
    return line;
}