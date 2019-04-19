//
// Created by St on 2019-04-11.
//

#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "MassIncrease.h"
#include "../Menu.h"
#include "../../data/Serializer.h"
#include "../../data/DataManager.h"
#include "../cJson/cJSON.h"
#include "../../util/FileUtil.h"
#include "MIguest.h"
#include "MIprovider.h"
#include "MImountings.h"
#include "MIselling.h"
#include "MIpurchase.h"
#include "MIorder.h"

#define MENU_CNT 7

Menu *miMenu;

void updatePrint();

void MassIncrease_init(){
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("    客  户"),
            STR_BUF("    销售商"),
            STR_BUF("    零部件"),
            STR_BUF("    销售记录"),
            STR_BUF("     购买记录"),
            STR_BUF("     订  单"),
            STR_BUF("    退出系统")
    };
    miMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_MASSINCREASE,STR_BUF("批量增加"));
}

void MassIncrease_inLoop(){
    Menu_inLoop(miMenu);
    if(READ_SPEC){
        updatePrint();
        if(SPEC_KEY == KEY_ENTER){
            switch (miMenu->cur) {
                case 0:
                    MIguest_init();
                    break;
                case 1:
                    MIprovider_init();
                    break;
                case 2:
                    MImountings_init();
                    break;
                case 3:
                    MIselling_init();
                    break;
                case 4:
                    MIpurchase_init();
                    break;
                case 5:
                    MIorder_init();
                    break;
                case 6:
                    DataManager_save(LITERAL("data"));
                    exit(0);
                default:
                    break;
            }
        }
        if(SPEC_KEY == KEY_ESC){
            UI_endScene();
        }
    }
}

int MassIncrease_render(int line){
    UI_printMidString(LITERAL("欢迎使用批量增加!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    UI_printMidString(LITERAL("请选择批量增加的内容："), line);
    line += 1;
    putchar('\n');
    line += Menu_render(miMenu, line);
    updatePrint();
    return line;
}

void updatePrint(){
    string instruction = NULL;
    switch (miMenu->cur) {
        case 0:
            instruction = LITERAL("批量增加客户信息。");
            break;
        case 1:
            instruction = LITERAL("批量增加销售商信息。");
            break;
        case 2:
            instruction = LITERAL("批量增加零部件信息。");
            break;
        case 3:
            instruction = LITERAL("批量增加销售记录信息。");
            break;
        case 4:
            instruction = LITERAL("批量增加购买记录信息。");
            break;
        case 5:
            instruction = LITERAL("批量增加订单信息。");
            break;
        default:
            instruction = LITERAL("");
    }
    UI_setFooterUpdate(instruction);
}
