//
// Created by guyis on 2019/4/16.
//

#include <assert.h>
#include "RecordInput.h"
#include "../UI.h"
#include "../Menu.h"
#include "../../data/TableMountings.h"
#include "../../data/DataManager.h"
#include "../UI_Utils.h"
#include "../Table.h"
#include "../../data/TableProvider.h"
#include "../../model/Forecase.h"

#define MENU_RECORD_CNT 6
#define TABLE_COLUMN_NUM 6

RecordParam CUR_REC_PARAM, nowParam;
enum RECORD_VIEW {
    MENU = 0, SELECT_MOUNT
} curView;
Menu *recordMenu;
Table *mountingTable;

void updateRecordMenuText();

void calcTotal();

void loadTableData();

stringbuf forPriceStr(double price);

/**
 * 初始化并进入读入记录页面
 * @param nowVal 当前值，若partId为-1则视为空
 */
void RecordInput_init(RecordParam nowVal) {
    READ_SPEC = true;
    /*
     * 初始化数据值
     */
    CUR_REC_PARAM = nowVal;
    curView = MENU; // 确定当前页面
    if (CUR_REC_PARAM.partId == -1) {
        CUR_REC_PARAM.id = -1;
        CUR_REC_PARAM.amount = 0;
        CUR_REC_PARAM.price = 0;
        CUR_REC_PARAM.total = 0;
        CUR_REC_PARAM.time = Time_getNow();
    }
    nowParam = CUR_REC_PARAM;
    /*
     * 菜单初始化
     */
    stringbuf menuItem[] = {
            STR_BUF("零配件：尚未选择"),
            STR_BUF("数量："),
            STR_BUF("价格："),
            STR_BUF("总价："),
            STR_BUF("时间："),
            STR_BUF("完成")
    };
    recordMenu = Menu_create(40, 9, menuItem, MENU_RECORD_CNT, 0);
    /*
     * 表格初始化
     */
    stringbuf columnName[] = {
            STR_BUF("类型"),
            STR_BUF("供货商"),
            STR_BUF("名称"),
            STR_BUF("库存"),
            STR_BUF("价格"),
            STR_BUF("预测(进货/销售)")
    };
    int columnWidth[] = {10, 25, 20, 10, 10, 25};
    mountingTable = Table_create(-1, 0, 106, 27, -1, -1);
    Table_setColumnTitle(mountingTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    //
    UI_setFooterUpdate(LITERAL("按下Enter键以选择/编辑"));
    UI_startScene(SCENE_RECORD_INPUT, STR_BUF("记录"));
    updateRecordMenuText();
}

void RecordInput_inLoop() {
    int intVal;
    double doubleVal;
    Time timeVal;
    if (curView == MENU) {
        Menu_inLoop(recordMenu);
        if (READ_SPEC) {
            if (SPEC_KEY == KEY_ENTER) {
                switch (recordMenu->cur) {
                    case 0: // 零配件
                        // 加载表格数据
                        loadTableData();
                        // 切换视图
                        curView = SELECT_MOUNT;
                        UI_render();
                        break;
                    case 1: // 数量
                        if (UI_inputInt(&intVal, LITERAL("请输入数量：")) && intVal > 0) {
                            nowParam.amount = intVal;
                            calcTotal();
                            updateRecordMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                        }
                        break;
                    case 2: // 价格
                        if (UI_inputDouble(&doubleVal, LITERAL("请输入单价：")) && doubleVal > 0) {
                            nowParam.price = doubleVal;
                            calcTotal();
                            updateRecordMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                        }
                        break;
                    case 3: // 总价
                        if (UI_inputDouble(&doubleVal, LITERAL("请输入总价：")) && doubleVal > 0) {
                            nowParam.total = doubleVal;
                            updateRecordMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                        }
                        break;
                    case 4: // 时间
                        if (UI_inputTime(&timeVal, LITERAL("请输入时间："))) {
                            nowParam.time = timeVal;
                            updateRecordMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                        }
                        break;
                    case 5: // 完成
                        CUR_REC_PARAM = nowParam;
                        UI_endScene();
                        break;
                }
            }
        }
    } else if (curView == SELECT_MOUNT) {
        Table_inLoop(mountingTable);
        UI_setFooterUpdate(Table_getSelection(mountingTable));
        if (READ_SPEC) {
            if (SPEC_KEY == KEY_ENTER) {
                Mountings *selected = GetById(Mountings, MOUNTINGS, mountingTable->cur);
                nowParam.partId = selected->id;
                nowParam.price = selected->price;
                calcTotal(); // 可能由于修改导致价格改变
                updateRecordMenuText();
                // 切换视图
                curView = MENU;
                UI_render();
            }
        }
    }
}

void loadTableData() {
    Table_clear(mountingTable);
    stringbuf line[TABLE_COLUMN_NUM];
    time_t curTime = time(NULL);
    ForEach(cur, MOUNTINGS) {
        Mountings *data = GetData(Mountings, cur);
        Provider *provider = GetById(Provider, PROVIDER, data->sellerId);
        double forcPurPrice = forecasePurchasePrice(curTime, data->id),
            forcSellPrice = forecaseSellingPrice(curTime, data->id);
        assert(provider); // provider期望不为空
        line[0] = Mountings_getTypeString(data->type);
        line[1] = concat(4, provider->name, LITERAL(" ("), provider->phone, LITERAL(")"));
        line[2] = cloneString(data->name);
        line[3] = toIntString(data->amount);
        line[4] = toRmbString(data->price);
        line[5] = concat(3, forPriceStr(forcPurPrice), LITERAL("/"), forPriceStr(forcSellPrice));
        Table_pushLine(mountingTable, line);
    }
    mountingTable->columnCur = 0;
    Table_setCurAndUpdate(mountingTable, nowParam.partId != -1 ? nowParam.partId: 1);
}

stringbuf forPriceStr(double price) {
    if (price > 0)
        return toRmbString(price);
    else
        return STR_BUF("数据不足");
}

int RecordInput_render(int line) {
    if (curView == MENU) {
        Menu_render(recordMenu, line);
    } else if (curView == SELECT_MOUNT) {
        UI_printMidString(LITERAL("按Enter键以选择零件："), line++);
        Table_render(mountingTable, line);
    }
}

/**
 * 获得用户输入的RecordParam
 * @return
 */
RecordParam RecordInput_result() {
    RecordParam ret = CUR_REC_PARAM;
    CUR_REC_PARAM.partId = -1;
    return ret;
}

/**
 * 自动计算总价
 */
void calcTotal() {
    if (nowParam.amount > 0 && nowParam.price > 0) {
        // 简单计算总价
        nowParam.total = nowParam.amount * nowParam.price;
    }
}

/**
 * 更新菜单文本
 */
void updateRecordMenuText() {
    if (nowParam.partId == -1) { // 还未选零配件
        Menu_setItemText(recordMenu, 0, STR_BUF("零配件：尚未选择"), false);
    } else {
        Mountings *mount = GetById(Mountings, MOUNTINGS, nowParam.partId);
        Menu_setItemText(recordMenu, 0, concat(2, LITERAL("零配件："), mount->name), false);
    }
    Menu_setItemText(recordMenu, 1, concat(2, LITERAL("数量："), toIntString(nowParam.amount)), false);
    Menu_setItemText(recordMenu, 2, concat(2, LITERAL("价格："), toRmbString(nowParam.price)), false);
    Menu_setItemText(recordMenu, 3, concat(2, LITERAL("总价："), toRmbString(nowParam.total)), false);
    Menu_setItemText(recordMenu, 4, concat(2, LITERAL("时间："), Time_toLocalString(nowParam.time)), true);
    UI_render();
    UI_setFooterUpdate(LITERAL("按下Enter键以选择/编辑"));
}