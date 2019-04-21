//
// Created by guyis on 2019/4/19.
//

#include "ViewSell.h"
#include "../../util/Time.h"
#include "../../data/TableProvider.h"
#include "../../core/Database.h"
#include "../../data/TableMountings.h"
#include "../Menu.h"
#include "../Table.h"
#include "../UI.h"
#include "../../model/Modify.h"
#include "RecordInput.h"
#include "ChooseMountingsType.h"
#include "ChooseGuest.h"
#include "TimeDurationInput.h"
#include "../UI_Utils.h"
#include "../../model/Consultation.h"
#include "../../model/Statistics.h"

#define SIDE_WIDTH 30
#define TABLE_WIDTH 90
#define TABLE_COLUMN_NUM 6

Table *sellTable;
Menu *sellMenu;
List *sellRecords;

// 查询条件
int curCond;
enum MountingsType sCondType;
Guest sCondGuest;
Time sCondTimeSt;
Time sCondTimeEd;

enum Column { // 表示当前用户在控制哪一栏
    MENU = 0, RECORD_TABLE
} curCul;

void ViewSell_inLoopMenu();

void ViewSell_inLoopTable();

void updateSTableData();

int getSelSellId();

void enterModifySellLogic();

/**
 * 销售记录查询页面：初始化
 */
void ViewSell_init() {
    /*
     * 右边栏：表格
     */
    stringbuf columnName[] = {
            STR_BUF("订单号"),
            STR_BUF("商品名"),
            STR_BUF("供货商"),
            STR_BUF("数量"),
            STR_BUF("价格"),
            STR_BUF("时间"),
    };
    int columnWidth[] = {6, 24, 13, 9, 14, 17};
    READ_SPEC = true;
    sellTable = Table_create(SIDE_WIDTH, 0, TABLE_WIDTH, 27, -1, -1);
    Table_setColumnTitle(sellTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    /*
     * 筛选条件选单
     */
    stringbuf menuName[] = {
            STR_BUF("  查看所有"),
            STR_BUF("  配件种类"),
            STR_BUF("  供 货 商"),
            STR_BUF("  时 间 段")
    };
    sellMenu = Menu_create(7, 0, menuName, 4, 0);
    /*
     * 初始化数据
     */
    sellRecords = Create(SellingRecord);
    curCul = MENU;
    // 初始化条件
    curCond = 0;
    sCondType = MOUNTINGS_MOUSE;
    sCondGuest.id = -1;
    sCondTimeSt = Time_getNow();
    sCondTimeEd = Time_getNow();
    //
    UI_setFooterUpdate(LITERAL(""));
    UI_startScene(SCENE_VIEW_SELL, STR_BUF("销售记录"));
    updateSTableData();
}

void ViewSell_inLoop() {
    /*
     * 切换逻辑
     */
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) {
            // 切换左右
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
                if (sellTable->cur == -1 && Database_size(sellRecords) > 0)
                    Table_setCurAndUpdate(sellTable, 1);
            } else if (curCul == RECORD_TABLE) {
                curCul = MENU;
            }
            UI_render();
            return;
        } else if (SPEC_KEY == KEY_ESC) {
            // 退出场景
            UI_endScene();
        }
    }
    /*
     * 分栏操作
     */
    if (curCul == MENU) {
        ViewSell_inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        ViewSell_inLoopTable();
    }
}

/**
 * 表格操作
 */
void ViewSell_inLoopTable() {
    Table_inLoop(sellTable);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_DEL) {
            if (EQUAL(LITERAL("y"), UI_inputString(LITERAL("是否确定要删除？[y/n]")))) {
                stringbuf reason = $init$;
                int sId = getSelSellId();
                if (deleteSellingRecord(sId, &reason)) {
                    UI_setFooterUpdate(LITERAL("删除成功！"));
                    updateSTableData();
                } else {
                    UI_setFooterUpdate(concat(2, LITERAL("删除失败！"), reason));
                }
            } else {
                UI_setFooterUpdate(LITERAL(""));
            }
        } else if (SPEC_KEY == 'X' || SPEC_KEY == 'x') {
            enterModifySellLogic();
        }
    }
}

void enterModifySellLogic() {
    int sId = getSelSellId();
    SellingRecord *record = GetById(SellingRecord, SELLING_RECORD, sId);
    RecordParam param = {
            .id = sId,
            .partId = record->partId,
            .price = record->price,
            .total = record->total,
            .amount = record->amount,
            .time = record->time
    };
    RecordInput_init(param);
}

int getSelSellId() {
    int sel = sellTable->cur, ind = 1;
    ForEach(cur, sellRecords) {
        SellingRecord *data = GetData(SellingRecord, cur);
        if (ind++ == sel) {
            return data->id;
        }
    }
    return -1;
}

/**
 * 菜单操作
 */
void ViewSell_inLoopMenu() {
    Menu_inLoop(sellMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (sellMenu->cur) {
                case 0: // 查看所有
                    curCond = 0;
                    updateSTableData();
                    break;
                case 1: // 配件种类
                    ChooseMountingsType_init(sCondType);
                    break;
                case 2: // 供货商
                    ChooseGuest_init(sCondGuest.id, 1);
                    break;
                case 3: // 时间段
                    TimeDurationInput_init();
                    break;
            }
        }
    }
}

int ViewSell_render(int line) {
    /*
     * 更新数据
     */
    // 类型
    if (ChooseMountingsType_hasResult()) {
        curCond = 1;
        sCondType = ChooseMountingsType_result();
        updateSTableData();
    }
    // 客户
    Guest ret = ChooseGuest_result();
    if (ret.id > 0 && ret.id != sCondGuest.id) {
        curCond = 2;
        sCondGuest = ret;
        updateSTableData();
    }
    // 时间段
    if (TimeDurationInput_hasResult()) {
        curCond = 3;
        sCondTimeSt = TimeDurationInput_resultSt();
        sCondTimeEd = TimeDurationInput_resultEd();
        updateSTableData();
    }
    // 修改
    RecordParam modRet = RecordInput_result();
    if (modRet.partId > 0) {
        SellingRecord *org = GetById(SellingRecord, SELLING_RECORD, modRet.id);
        stringbuf reason = $init$;
        SellingRecord after = {
                .orderId = org->orderId,
                .partId = modRet.partId,
                .time = modRet.time,
                .amount = modRet.amount,
                .total = modRet.total,
                .price = modRet.price,
                .guestId = org->guestId,
                .status = org->status
        };
        if (modifyOrderOfSellingRecord(org->orderId, modRet.id, &after, &reason)) {
            UI_setFooterUpdate(LITERAL("修改成功！"));
        } else {
            UI_setFooterUpdate(concat(2, LITERAL("修改失败！"), reason));
        }
    }
    /*
     * 右侧试图
     */
    Table_render(sellTable, line);
    /*
     * 左侧视图
     */
    line += 1;
    UI_printMidStringAt(LITERAL("当前操作"), 0, 0, 30, line);
    if (curCul == MENU)
        UI_printMidStringAt(LITERAL("菜单"), 0, 2, 30, line);
    else
        UI_printMidStringAt(LITERAL("表格"), 0, 2, 30, line);
    line += 5;
    UI_printMidStringAt(LITERAL("当前条件"), 0, 0, 30, line);
    switch (curCond) {
        case 0:
            UI_printMidStringAt(LITERAL("无"), 0, 2, 30, line);
            break;
        case 1:
            UI_printMidStringAt(concat(2, LITERAL("配件种类："), Mountings_getTypeString(sCondType)), 0, 2, 30, line);
            break;
        case 2:
            UI_printMidStringAt(concat(2, LITERAL("客户："), sCondGuest.name), 0, 2, 30, line);
            break;
        case 3:
            UI_printMidStringAt(concat(3, LITERAL("时间段："),
                                       Time_toLocalString(sCondTimeSt), LITERAL("-")), 0, 2, 30, line);
            UI_printMidStringAt(Time_toLocalString(sCondTimeEd), 0, 3, 30, line);
            break;
    }
    line += 5;
    UI_printMidStringAt(LITERAL("操作说明"), 0, 0, 30, line);
    UI_printMidStringAt(LITERAL("Tab - 切换表格/菜单"), 0, 2, 30, line);
    UI_printMidStringAt(LITERAL("Enter - (菜单)选择筛选条件"), 0, 3, 30, line);
    UI_printMidStringAt(LITERAL("X - (表格)修改记录"), 0, 4, 30, line);
    UI_printMidStringAt(LITERAL("DEL - (表格)删除记录"), 0, 5, 30, line);
    UI_printMidStringAt(LITERAL("Esc - 退出页面"), 0, 6, 30, line);
    line += 9;
    Menu_render(sellMenu, line);
    return line;
}


/*
 * 数据更新
 */

/**
 * 根据条件更新数据表
 */
void updateSTableData() {
    Table_clear(sellTable);
    // Database_destroy(purchaseRecords);
    switch (curCond) {
        case 0: // 查看所有
            sellRecords = QueryAll_Sel();
            break;
        case 1: // 配件种类
            sellRecords = AccessoryOut(sCondType);
            break;
        case 2: // 供货商
            sellRecords = Client(sCondGuest.id);
            break;
        case 3: // 时间段
            sellRecords = Print_Sellingrecord(sCondTimeSt, sCondTimeEd);
            break;
    }
    stringbuf line[TABLE_COLUMN_NUM];
    ForEach(cur, sellRecords) {
        SellingRecord *data = GetData(SellingRecord, cur);
        Mountings *mountings = GetById(Mountings, MOUNTINGS, data->partId);
        Provider *provider = GetById(Provider, PROVIDER, mountings->sellerId);
        Guest *guest = GetById(Guest, PROVIDER, data->guestId);
        Order *order = GetById(Order, ORDER, data->orderId);

        line[0] = concat(2, toIntString(data->orderId), order->type == ORDER_WHOLE_SALE ? LITERAL("批"): $init$);
        line[1] = concat(4, mountings->name, LITERAL(" ("), provider->name, LITERAL(")"));
        line[2] = guest->name;
        line[3] = toIntString(data->amount);
        line[4] = data->status == SELLING_GIFT ? STR_BUF("礼品"): toRmbString(data->total);
        line[5] = Time_toLocalString(data->time);
        Table_pushLine(sellTable, line);
    }
    if (Database_size(sellRecords) > 0)
        Table_setCur(sellTable, 1);
    UI_render();
}
