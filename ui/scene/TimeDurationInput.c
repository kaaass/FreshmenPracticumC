//
// Created by guyis on 2019/4/20.
//

#include "TimeDurationInput.h"
#include "../Menu.h"
#include "../UI.h"
#include "../UI_Utils.h"

Time CUR_TIME_ST;
Time CUR_TIME_ED;
bool hasResultTime = false;

Menu *inputTimeMenu;

void updateTimeMenuText();

void TimeDurationInput_init() {
    /*
     * 初始化菜单
     */
    stringbuf menuName[] = {
            STR_BUF("开始时间：00月00日 00:00:00"),
            STR_BUF("结束时间：00月00日 00:00:00"),
            STR_BUF("完成")
    };
    inputTimeMenu = Menu_create(-1, 10, menuName, 3, 0);
    /*
     * 初始化数据
     */
    CUR_TIME_ST = Time_parseTime(0);
    CUR_TIME_ED = Time_getNow();
    hasResultTime = false;
    //
    UI_setFooterUpdate(LITERAL("按下Enter键以输入/选择"));
    UI_startScene(SCENE_TIME_DURATION_INPUT, STR_BUF("输入时间区间"));
    updateTimeMenuText();
}

void TimeDurationInput_inLoop() {
    Time timeVal;
    Menu_inLoop(inputTimeMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (inputTimeMenu->cur) {
                case 0:
                    if (UI_inputTime(&timeVal, LITERAL("请输入开始时间："))) {
                        CUR_TIME_ST = timeVal;
                        updateTimeMenuText();
                    } else {
                        UI_render();
                        UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                    }
                    break;
                case 1:
                    if (UI_inputTime(&timeVal, LITERAL("请输入结束时间："))) {
                        CUR_TIME_ED = timeVal;
                        updateTimeMenuText();
                    } else {
                        UI_render();
                        UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                    }
                    break;
                case 2:
                    if (CUR_TIME_ST.timeStamp > CUR_TIME_ED.timeStamp) {
                        UI_setFooterUpdate(LITERAL("开始时间不能比结束时间晚！"));
                        return;
                    }
                    hasResultTime = true;
                    UI_endScene();
                    break;
            }
        }
    }
}

void updateTimeMenuText() {
    UI_setFooterUpdate(LITERAL("按下Enter键以输入/选择"));
    Menu_setItemText(inputTimeMenu, 0, concat(2, LITERAL("开始时间："), Time_toLocalString(CUR_TIME_ST)), false);
    Menu_setItemText(inputTimeMenu, 1, concat(2, LITERAL("结束时间："), Time_toLocalString(CUR_TIME_ED)), false);
    UI_render();
}

int TimeDurationInput_render(int line) {
    Menu_render(inputTimeMenu, line);
}

Time TimeDurationInput_resultSt() {
    hasResultTime = false;
    return CUR_TIME_ST;
}

Time TimeDurationInput_resultEd() {
    hasResultTime = false;
    return CUR_TIME_ED;
}

bool TimeDurationInput_hasResult() {
    return hasResultTime;
}
