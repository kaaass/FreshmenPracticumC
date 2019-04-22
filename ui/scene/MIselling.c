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
#include "MIselling.h"

#define MENU_CNT 1

Menu *sellingMenu;

void MIselling_init(){
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("请输入文件路径"),
    };
    sellingMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_MISELLING,STR_BUF("销售记录"));
}

void MIselling_inLoop(){
    Menu_inLoop(sellingMenu);
    if(READ_SPEC){
        cJSON *json;
        string dir;
        dir = UI_inputString(LITERAL("请输入文件路径："));
        stringbuf content;
        // 检测文件存在
        if (!isExist(CSTR(dir))) {
            string instruction = LITERAL("文件不存在，按Esc返回上一页面");
            UI_setFooterUpdate(instruction);
            if(SPEC_KEY == KEY_ESC)
                UI_endScene();
        }
        // SellingRecord
        else{
            content = readStringFromFile(CSTR(dir));
            json = cJSON_Parse(U8_CSTR(content));
            ForEach(cur,json){
                SellingRecord *record = GetData(SellingRecord,cur);
                Database_pushBack(SELLING_RECORD,Data(SellingRecord,record));
            }
            cJSON_Delete(json);
            string instruction = LITERAL("导入成功，按Esc返回上一页面");
            UI_setFooterUpdate(instruction);
            if(SPEC_KEY == KEY_ESC)
                UI_endScene();
        }
        if(SPEC_KEY == KEY_ESC)
            UI_endScene();
    }
}

int MIselling_render(int line){
    UI_printMidString(LITERAL("欢迎使用批量增加!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    UI_printMidString(LITERAL("请选择批量增加的内容："), line);
    line += 1;
    putchar('\n');
    line += Menu_render(sellingMenu, line);
    return line;
}