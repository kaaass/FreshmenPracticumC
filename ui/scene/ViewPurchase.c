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

#define SIDE_WIDTH 30
#define TABLE_WIDTH 90
#define TABLE_COLUMN_NUM 6

Table *purchaseTable;
Menu *purchaseMenu;
List *purchaseRecords;

// 查询条件
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
            STR_BUF("生产厂商"),
            STR_BUF("供货商"),
            STR_BUF("数量"),
            STR_BUF("价格"),
    };
    int columnWidth[] = {8, 16, 20, 20, 9, 10};
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
    pCondType = MOUNTINGS_CPU;
    pCondProvider.id = -1;
    pCondTimeSt = Time_getNow();
    pCondTimeEd = Time_getNow();
    //
    updatePTableData();
    UI_setFooterUpdate(LITERAL(""));
    UI_startScene(SCENE_VIEW_PURCHASE, STR_BUF("进货记录"));
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
}

/**
 * 菜单操作
 */
void ViewPurchase_inLoopMenu() {
    Menu_inLoop(purchaseMenu);
}

int ViewPurchase_render(int line) {
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
    UI_printMidStringAt(LITERAL("操作说明"), 0, 0, 30, line);
    UI_printMidStringAt(LITERAL("Tab - 切换表格/菜单"), 0, 2, 30, line);
    UI_printMidStringAt(LITERAL("Enter - (菜单)选择筛选条件"), 0, 3, 30, line);
    UI_printMidStringAt(LITERAL("X - (表格)修改记录"), 0, 4, 30, line);
    UI_printMidStringAt(LITERAL("R - (表格)删除记录"), 0, 5, 30, line);
    UI_printMidStringAt(LITERAL("Esc - 退出页面"), 0, 6, 30, line);
    line += 10;
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
}