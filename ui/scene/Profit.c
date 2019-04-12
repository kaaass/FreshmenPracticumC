//
// Created by hasee on 2019/4/11.
//

#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "Profit.h"
#include "../UI_Utils.h"

void Profit_init() {
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Enter键以返回..."));
    UI_startScene(SCENE_ABOUT, STR_BUF("利润"));
}

void Profit_inLoop() {
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键返回
            UI_endScene();
        }
    }
}

int Profit_render(int line){
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    putchar('\n'); line += 1;
    UI_printMidString(LITERAL("营 业 额： "), line);
    printf("%.2lf",Sell_total());line++;
    UI_printMidString(LITERAL("净 利 润： "), line);
    printf("%.2lf",Profits());line++;
    return line;
}