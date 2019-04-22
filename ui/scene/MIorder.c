//
// Created by St on 2019-04-18.
//

#include <stdio.h>
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "../Menu.h"
#include "../../data/Serializer.h"
#include "../../data/DataManager.h"
#include "../cJson/cJSON.h"
#include "../../util/FileUtil.h"
#include "MIorder.h"

#define MENU_CNT 1

Menu *orderMenu;

void MIorder_init(){
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("请输入文件路径"),
    };
    orderMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_MIORDER,STR_BUF("销售记录"));
}

void MIorder_inLoop(){
    Menu_inLoop(orderMenu);
    if(READ_SPEC){
        if(SPEC_KEY == KEY_ESC)
            UI_endScene();
        cJSON *json;
        string dir;
        dir = UI_inputString(LITERAL("请输入文件路径："));
        stringbuf path, content;
        // 检测文件存在
        if (!isExist(CSTR(dir))) {
            string instruction = LITERAL("文件不存在，按Esc返回上一页面");
            UI_setFooterUpdate(instruction);
            if(SPEC_KEY == KEY_ESC)
                UI_endScene();
        }
        // Order
        else{
            path = LITERAL("/Order.json");
            path = concat(2, dir, path);
            content = readStringFromFile(CSTR(path));
            json = cJSON_Parse(U8_CSTR(content));
            ForEach(cur,json){
                Order *record = GetData(Order,cur);
                Database_pushBack(ORDER,Data(Order,record));
            }
            cJSON_Delete(json);
            $STR_BUF(path);
        }
    }
}

int MIorder_render(int line){
    UI_printMidString(LITERAL("欢迎使用批量增加!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    UI_printMidString(LITERAL("请选择批量增加的内容："), line);
    line += 1;
    putchar('\n');
    line += Menu_render(orderMenu, line);
    return line;
}