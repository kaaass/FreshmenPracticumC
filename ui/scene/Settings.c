//
// Created by guyis on 2019/4/21.
//

#include <cstring_jslike.h>
#include "Settings.h"
#include "../UI.h"
#include "../Menu.h"
#include "../../core/Config.h"
#include "../UI_Utils.h"

Menu *setMenu;

void updateSettingMenuText();

void Settings_init() {
    /*
     * 初始化菜单
     */
    stringbuf menuName[] = {
            STR_BUF("小赠品限额："),
            STR_BUF("大赠品限额：")
    };
    setMenu = Menu_create(-1, 10, menuName, 2, 0);
    //
    READ_SPEC = true;
    UI_startScene(SCENE_SETTINGS, STR_BUF("设置"));
    updateSettingMenuText();
}

void updateSettingMenuText() {
    double boundLow, boundHigh;
    boundLow = Config_optDouble(LITERAL("giftSendingBound1"), 100);
    boundHigh = Config_optDouble(LITERAL("giftSendingBound2"), 1000);
    UI_setFooterUpdate(LITERAL("按下Esc键以返回..."));
    Menu_setItemText(setMenu, 0, concat(2, LITERAL("小赠品限额："), toRmbString(boundLow)), false);
    Menu_setItemText(setMenu, 1, concat(2, LITERAL("大赠品限额："), toRmbString(boundHigh)), false);
    UI_render();
}

void Settings_inLoop() {
    double doubVal;
    Menu_inLoop(setMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        } else if (SPEC_KEY == KEY_ENTER) {
            double boundLow, boundHigh;
            boundLow = Config_optDouble(LITERAL("giftSendingBound1"), 100);
            boundHigh = Config_optDouble(LITERAL("giftSendingBound2"), 1000);
            switch (setMenu->cur) {
                case 0:
                    if (UI_inputDouble(&doubVal, LITERAL("请输入小赠品限额："))) {
                        if (doubVal <= boundHigh) {
                            Config_setDouble(LITERAL("giftSendingBound1"), doubVal);
                            updateSettingMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("小赠品限额不能大于大赠品限额！"));
                        }
                    } else {
                        UI_render();
                        UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                    }
                    break;
                case 1:
                    if (UI_inputDouble(&doubVal, LITERAL("请输入大赠品限额："))) {
                        if (doubVal >= boundLow) {
                            Config_setDouble(LITERAL("giftSendingBound2"), doubVal);
                            updateSettingMenuText();
                        } else {
                            UI_render();
                            UI_setFooterUpdate(LITERAL("大赠品限额不能小于小赠品限额！"));
                        }
                    } else {
                        UI_render();
                        UI_setFooterUpdate(LITERAL("输入格式不正确！"));
                    }
                    break;
            }
        }
    }
}

int Settings_render(int line) {
    Menu_render(setMenu, line);
    return line;
}
