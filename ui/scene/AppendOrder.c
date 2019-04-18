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
#include "RecordInput.h"
#include "../../data/TableMountings.h"
#include "../../data/TableProvider.h"
#include "../../data/DataManager.h"

#define MENU_CNT 3

enum OrderType CUR_TYPE;

Menu *selectMenu;
Menu *appendMenu;
Table *recordTable;
Guest curGuest;
float totalPrice;

List *records;

enum Column {
    MENU = 0, RECORD_TABLE
} curCul;

bool makeAndSaveOrder();

void updataRecordTable();

void deleteRecord();

#define SIDE_WIDTH 30
#define TABLE_COLUMN_NUM 5
#define TABLE_WIDTH 90
#define MENU_OP_CNT 6

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
    int columnWidth[] = {20, 8, 16, 16, 24};
    recordTable = Table_create(SIDE_WIDTH, 0, TABLE_WIDTH, CON_HEIGHT - 4, -1, -1);
    Table_setColumnTitle(recordTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    /*
     * 操作选单
     */
    stringbuf menuName[] = {
            STR_BUF("  增加记录"),
            STR_BUF("  修改选中"),
            STR_BUF("  删除选中"),
            STR_BUF("  设置对象"),
            STR_BUF("   完  成"),
            STR_BUF("   返  回")
    };
    appendMenu = Menu_create(7, 0, menuName, MENU_OP_CNT, 0);
    /*
     * 初始化数据
     */
    records = Create(RecordParam);
    curGuest.id = -1;
    curGuest.name = STR_BUF("尚未选择");
    curGuest.phone = STR_BUF("NaN");
    totalPrice = 0;
    curCul = MENU;
    UI_setFooterUpdate(LITERAL("当前为菜单，使用Tab切换至表格"));
    UI_startScene(SCENE_APPEND_ORDER, STR_BUF("新增记录"));
    SelectOrderType_init();
}

void AppendOrder_inLoop() {
    if (curCul == MENU) { // 菜单
        Menu_inLoop(appendMenu);
    } else if (curCul == RECORD_TABLE) { // 表格
        Table_inLoop(recordTable);
    }
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) { // 选单切换
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
                // 更新表格选中项
                if (Database_size(records) > 0 && recordTable->cur < 0)
                    Table_setCurAndUpdate(recordTable, 1);
            } else if (curCul == RECORD_TABLE) {
                curCul = MENU;
            }
        }
        if (curCul == MENU) {
            UI_setFooterUpdate(LITERAL("当前为菜单，使用Tab切换至表格"));
        } else if (curCul == RECORD_TABLE) {
            UI_setFooterUpdate(LITERAL("当前为表格，使用Tab切换至菜单"));
        }
        if (SPEC_KEY == KEY_ENTER) {
            if (curCul == MENU) { // 菜单下的Enter
                switch (appendMenu->cur) {
                    case 0: // 增加
                        RecordInput_init((RecordParam) {.partId = -1});
                        break;
                    case 1:; // 修改
                        if (recordTable->cur >= 1) {
                            RecordParam *cur = GetById(RecordParam, records, recordTable->cur);
                            RecordInput_init(*cur);
                        } else {
                            UI_setFooterUpdate(LITERAL("请先选中一条记录！"));
                        }
                        break;
                    case 2: // 删除
                        if (recordTable->cur >= 1) {
                            deleteRecord();
                        } else {
                            UI_setFooterUpdate(LITERAL("请先选中一条记录！"));
                        }
                        break;
                    case 3: // 设置客户/供货商
                        ChooseGuest_init(curGuest.id, CUR_TYPE == ORDER_PURCHASE ? 1: 0);
                        break;
                    case 4: // 完成
                        if (makeAndSaveOrder())
                            UI_endScene();
                        break;
                    case 5:
                        UI_endScene();
                        break;
                }
            }
        }
    }
}

int AppendOrder_render(int line) {
    /*
     * 更新数据
     */
    // 记录
    RecordParam param = RecordInput_result();
    if (param.partId > 0) {
        if (param.id <= 0) {
            Database_pushBack(records, Data(RecordParam, &param));
        } else {
            Database_modifyById(records, param.id, Data(RecordParam, &param));
        }
        updataRecordTable();
    }
    // 客户
    Guest ret = ChooseGuest_result();
    if (ret.id > 0 && ret.id != curGuest.id)
        curGuest = ret;
    /*
     * 右侧视图
     */
    UI_printMidStringAt(LITERAL("待存记录："), SIDE_WIDTH, 0, TABLE_WIDTH, line++);
    Table_render(recordTable, line);
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
    line += 4;
    if (CUR_TYPE == ORDER_PURCHASE)
        UI_printMidStringAt(LITERAL("供货商"), 0, 0, 30, line);
    else
        UI_printMidStringAt(LITERAL("客户"), 0, 0, 30, line);
    UI_printMidStringAt(curGuest.name, 0, 2, 30, line);
    UI_printMidStringAt(curGuest.phone, 0, 3, 30, line);
    line += 5;
    UI_printMidStringAt(LITERAL("当前总价"), 0, 1, 30, line);
    UI_printMidStringAt(toRmbString(totalPrice), 0, 3, 30, line);
    line += 5;
    Menu_render(appendMenu, ++line);
    return line;
}

/**
 * 更新显示记录表格的内容
 */
void updataRecordTable() {
    Table_clear(recordTable);
    stringbuf line[5];
    totalPrice = 0;
    ForEach(cur, records) {
        RecordParam *data = GetData(RecordParam, cur);
        Mountings *mounting = GetById(Mountings, MOUNTINGS, data->partId);
        Provider *provider = GetById(Provider, PROVIDER, mounting->sellerId);
        line[0] = concat(4, mounting->name, LITERAL(" ("), provider->name, LITERAL(")"));
        line[1] = toIntString(data->amount);
        line[2] = toRmbString(data->price);
        line[3] = toRmbString(data->total);
        line[4] = Time_toLocalString(data->time);
        Table_pushLine(recordTable, line);
        totalPrice += data->total;
    }
    UI_render();
}

/*
 * 删除一条记录
 */
void deleteRecord() {
    Database_removeByCursor(records, Database_getCursorById(records, recordTable->cur));
    Table_setCur(recordTable, -1);
    updataRecordTable();
}

bool makeAndSaveOrder() {
    // 检查记录表不为空
    if (Database_size(records) <= 0) {
        UI_setFooterUpdate(LITERAL("请至少添加一条记录！"));
        return false;
    }
    // 检查是否选择客户
    if (curGuest.id < 1) {
        UI_setFooterUpdate(LITERAL("请设置记录对象！"));
        return false;
    }
    // 后台逻辑检查
    stringbuf info;
    if (!Insert_checkForAppend(records, curGuest, CUR_TYPE, totalPrice, &info)) {
        if (info != NULL) {
            UI_setFooterUpdate(info);
            $STR_BUF(info);
        }
        return false;
    }
    // 保存逻辑
    Insert_appendOrderLogic(records, curGuest, CUR_TYPE);
    return true;
}

/*
 * 选择类型页面
 */

void SelectOrderType_init() {
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    进货记录"),
            STR_BUF("    销售记录"),
            STR_BUF("    批发销售")
    };
    selectMenu = Menu_create(-1, 10, name, MENU_CNT, CUR_TYPE);
    UI_setFooterUpdate(LITERAL("按Enter键以选择，按Esc以返回主页"));
    UI_startScene(SCENE_SELECT_ORDER_TYPE, STR_BUF("选择订单类型"));
}

void SelectOrderType_inLoop() {
    Menu_inLoop(selectMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键选择
            CUR_TYPE = selectMenu->cur;
            UI_endScene();
        } else if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
            UI_endScene();
        }
    }
}

int SelectOrderType_render(int line) {
    UI_printMidString(LITERAL("请选择订单类型："), line++);
    Menu_render(selectMenu, line);
    return line;
}