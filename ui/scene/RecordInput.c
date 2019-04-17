//
// Created by guyis on 2019/4/16.
//

#include "RecordInput.h"
#include "../UI.h"
#include "../Menu.h"
#include "../../data/TableMountings.h"
#include "../../data/DataManager.h"

#define MENU_RECORD_CNT 6

RecordParam CUR_REC_PARAM;
enum RECORD_VIEW {
    MENU = 0, SELECT_MOUNT
} curView;
Menu *recordMenu;

void updateRecordMenuText();

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
        CUR_REC_PARAM.amount = 0;
        CUR_REC_PARAM.price = 0;
        CUR_REC_PARAM.total = 0;
        CUR_REC_PARAM.time = Time_getNow();
    }
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
    updateRecordMenuText();
    //
    UI_setFooterUpdate(LITERAL("按下Enter键以选择/编辑"));
    UI_startScene(SCENE_RECORD_INPUT, STR_BUF("记录"));
}

void RecordInput_inLoop() {
    if (curView == MENU) {
        Menu_inLoop(recordMenu);
    }
}

int RecordInput_render(int line) {
    if (curView == MENU) {
        Menu_render(recordMenu, line);
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

void updateRecordMenuText() {
    stringbuf menuItem[] = {
            STR_BUF("零配件："),
            STR_BUF("数量："),
            STR_BUF("价格："),
            STR_BUF("总价："),
            STR_BUF("时间："),
            STR_BUF("完成")
    };
    if (CUR_REC_PARAM.partId == -1) { // 还未选零配件
        Menu_setItemText(recordMenu, 0, STR_BUF("零配件：尚未选择"));
    } else {
        Mountings *mount = GetById(Mountings, MOUNTINGS, CUR_REC_PARAM.partId);
        Menu_setItemText(recordMenu, 0, concat(2, LITERAL("零配件："), mount->name));
    }
    Menu_setItemText(recordMenu, 1, concat(2, LITERAL("数量："), toIntString(CUR_REC_PARAM.amount)));
    Menu_setItemText(recordMenu, 2, concat(2, LITERAL("价格："), toRmbString(CUR_REC_PARAM.price)));
    Menu_setItemText(recordMenu, 3, concat(2, LITERAL("总价："), toRmbString(CUR_REC_PARAM.total)));
    Menu_setItemText(recordMenu, 4, concat(2, LITERAL("时间："), Time_toLocalString(CUR_REC_PARAM.time)));
}