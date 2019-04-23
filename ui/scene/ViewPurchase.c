//
// Created by guyis on 2019/4/19.
//

#include <cstring_jslike.h>
#include "ViewPurchase.h"
#include "../UI.h"
#include "../Table.h"
#include "../Menu.h"
#include "../../data/TablePurchaseRecord.h"
#include "../../data/TableMountings.h"
#include "../../data/TableProvider.h"
#include "../UI_Utils.h"
#include "../../data/DataManager.h"
#include "../../model/Consultation.h"
#include "../../model/Statistics.h"
#include "ChooseGuest.h"
#include "ChooseMountingsType.h"
#include "TimeDurationInput.h"
#include "../../model/Modify.h"
#include "RecordInput.h"

#define SIDE_WIDTH 30
#define TABLE_WIDTH 90
#define TABLE_COLUMN_NUM 6

Table *purchaseTable;
Menu *purchaseMenu;
List *purchaseRecords;

// 查询条件
int curCond;
enum MountingsType pCondType;
Provider pCondProvider;
Time pCondTimeSt;
Time pCondTimeEd;

enum Column { // 表示当前用户在控制哪一栏
    MENU = 0, RECORD_TABLE
} curCul;

void ViewPurchase_inLoopMenu();

void ViewPurchase_inLoopTable();

void updatePTableData();

int getSelPurchaseId();

void enterModifyLogic();

/**
 * 进货记录查询页面：初始化
 */
void ViewPurchase_init() {
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
    purchaseTable = Table_create(SIDE_WIDTH, 0, TABLE_WIDTH, 27, -1, -1);
    Table_setColumnTitle(purchaseTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    /*
     * 筛选条件选单
     */
    stringbuf menuName[] = {
            STR_BUF("  查看所有"),
            STR_BUF("  配件种类"),
            STR_BUF("  供 货 商"),
            STR_BUF("  时 间 段")
    };
    purchaseMenu = Menu_create(7, 0, menuName, 4, 0);
    /*
     * 初始化数据
     */
    purchaseRecords = Create(PurchaseRecord);
    curCul = MENU;
    // 初始化条件
    curCond = 0;
    pCondType = MOUNTINGS_MOUSE;
    pCondProvider.id = -1;
    pCondTimeSt = Time_getNow();
    pCondTimeEd = Time_getNow();
    //
    UI_setFooterUpdate(LITERAL(""));
    UI_startScene(SCENE_VIEW_PURCHASE, STR_BUF("进货记录"));
    updatePTableData();
}

void ViewPurchase_inLoop() {
    /*
     * 切换逻辑
     */
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) {
            // 切换左右
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
                if (purchaseTable->cur == -1 && Database_size(purchaseRecords) > 0)
                    Table_setCurAndUpdate(purchaseTable, 1);
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
        ViewPurchase_inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        ViewPurchase_inLoopTable();
    }
}

/**
 * 表格操作
 */
void ViewPurchase_inLoopTable() {
    Table_inLoop(purchaseTable);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_DEL) {
            if (UI_askFor(LITERAL("是否确定要删除？"))) {
                stringbuf reason = $init$;
                int pId = getSelPurchaseId();
                if (deletePurchaseRecord(pId, &reason)) {
                    UI_setFooterUpdate(LITERAL("删除成功！"));
                    updatePTableData();
                } else {
                    UI_setFooterUpdate(concat(2, LITERAL("删除失败！"), reason));
                }
            } else {
                UI_setFooterUpdate(LITERAL(""));
            }
        } else if (SPEC_KEY == 'X' || SPEC_KEY == 'x') {
            enterModifyLogic();
        }
    }
}

void enterModifyLogic() {
    int pId = getSelPurchaseId();
    PurchaseRecord *record = GetById(PurchaseRecord, PURCHASE_RECORD, pId);
    RecordParam param = {
            .id = pId,
            .partId = record->partId,
            .price = record->price,
            .total = record->total,
            .amount = record->amount,
            .time = record->time
    };
    RecordInput_init(param);
}

int getSelPurchaseId() {
    int sel = purchaseTable->cur, ind = 1;
    ForEach(cur, purchaseRecords) {
        PurchaseRecord *data = GetData(PurchaseRecord, cur);
        if (ind++ == sel) {
            return data->id;
        }
    }
    return -1;
}

/**
 * 菜单操作
 */
void ViewPurchase_inLoopMenu() {
    Menu_inLoop(purchaseMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (purchaseMenu->cur) {
                case 0: // 查看所有
                    curCond = 0;
                    updatePTableData();
                    break;
                case 1: // 配件种类
                    ChooseMountingsType_init(pCondType);
                    break;
                case 2: // 供货商
                    ChooseGuest_init(pCondProvider.id, 1);
                    break;
                case 3: // 时间段
                    TimeDurationInput_init();
                    break;
            }
        }
    }
}

int ViewPurchase_render(int line) {
    /*
     * 更新数据
     */
    // 类型
    if (ChooseMountingsType_hasResult()) {
        curCond = 1;
        pCondType = ChooseMountingsType_result();
        updatePTableData();
    }
    // 客户
    Guest ret = ChooseGuest_result();
    if (ret.id > 0 && ret.id != pCondProvider.id) {
        curCond = 2;
        pCondProvider.id = ret.id;
        pCondProvider.name = ret.name;
        pCondProvider.phone = ret.phone;
        updatePTableData();
    }
    // 时间段
    if (TimeDurationInput_hasResult()) {
        curCond = 3;
        pCondTimeSt = TimeDurationInput_resultSt();
        pCondTimeEd = TimeDurationInput_resultEd();
        updatePTableData();
    }
    // 修改
    RecordParam modRet = RecordInput_result();
    if (modRet.partId > 0) {
        PurchaseRecord *org = GetById(PurchaseRecord, PURCHASE_RECORD, modRet.id);
        stringbuf reason = $init$;
        PurchaseRecord after = {
                .orderId = org->orderId,
                .partId = modRet.partId,
                .time = modRet.time,
                .amount = modRet.amount,
                .total = modRet.total,
                .price = modRet.price,
                .sellerId = org->sellerId,
                .status = org->status
        };
        if (modifyOrderOfPurchaseRecord(org->orderId, modRet.id, &after, &reason)) {
            UI_setFooterUpdate(LITERAL("修改成功！"));
        } else {
            UI_setFooterUpdate(concat(2, LITERAL("修改失败！"), reason));
        }
    }
    /*
     * 右侧试图
     */
    Table_render(purchaseTable, line);
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
            UI_printMidStringAt(concat(2, LITERAL("配件种类："), Mountings_getTypeString(pCondType)), 0, 2, 30, line);
            break;
        case 2:
            UI_printMidStringAt(concat(2, LITERAL("供货商："), pCondProvider.name), 0, 2, 30, line);
            break;
        case 3:
            UI_printMidStringAt(concat(3, LITERAL("时间段："),
                    Time_toLocalString(pCondTimeSt), LITERAL("-")), 0, 2, 30, line);
            UI_printMidStringAt(Time_toLocalString(pCondTimeEd), 0, 3, 30, line);
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
    Menu_render(purchaseMenu, line);
    return line;
}

/*
 * 数据更新
 */

/**
 * 根据条件更新数据表
 */
void updatePTableData() {
    Table_clear(purchaseTable);
    // Database_destroy(purchaseRecords);
    switch (curCond) {
        case 0: // 查看所有
            purchaseRecords = QueryAll_Pur();
            break;
        case 1: // 配件种类
            purchaseRecords = AccessoryIn(pCondType);
            break;
        case 2: // 供货商
            purchaseRecords = Supplier(pCondProvider.id);
            break;
        case 3: // 时间段
            purchaseRecords = Print_Purchaserecord(pCondTimeSt, pCondTimeEd);
            break;
    }
    stringbuf line[TABLE_COLUMN_NUM];
    ForEach(cur, purchaseRecords) {
        PurchaseRecord *data = GetData(PurchaseRecord, cur);
        Mountings *mountings = GetById(Mountings, MOUNTINGS, data->partId);
        Provider *provider = GetById(Provider, PROVIDER, mountings->sellerId);
        Provider *seller = GetById(Provider, PROVIDER, data->sellerId);
        line[0] = toIntString(data->orderId);
        line[1] = concat(4, mountings->name, LITERAL(" ("), provider->name, LITERAL(")"));
        line[2] = seller->name;
        line[3] = toIntString(data->amount);
        line[4] = toRmbString(data->total);
        line[5] = Time_toLocalString(data->time);
        Table_pushLine(purchaseTable, line);
    }
    if (Database_size(purchaseRecords) > 0)
        Table_setCur(purchaseTable, 1);
    UI_render();
}