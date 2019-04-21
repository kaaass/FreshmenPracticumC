//
// Created by hasee on 2019/4/11.
//


#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "Profit.h"
#include "../UI_Utils.h"
#include "../../model/Statistics.h"

void Profit_init() {
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按ESC键返回上一页"));
    UI_startScene(SCENE_PROFIT_SITUATION, STR_BUF("利润"));
}

void Profit_inLoop() {
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

int Profit_render(int line) {
    line += 5;
    UI_printMidString(LITERAL("营 业 额"), line++);
    UI_printMidString(toRmbString(Sell_total()), line++);
    line += 1;
    UI_printMidString(LITERAL("净 利 润"), line++);
    UI_printMidString(toRmbString(Profits()), line++);
    return line;
}