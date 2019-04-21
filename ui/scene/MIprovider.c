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
#include "MIprovider.h"

#define MENU_CNT 1

Menu *providerMenu;

void MIprovider_init(){
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("请输入文件路径"),
    };
    providerMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_MIPROVIDER,STR_BUF("供货商"));
}

void MIprovider_inLoop(){
    cJSON *json;
    string dir;
    dir = UI_inputString(LITERAL("请输入文件路径："));
    stringbuf path, content;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        string instruction = LITERAL("文件不存在，按Esc返回上一页面");
        UI_setFooterUpdate(instruction);
    }
    // Provider
    else{
        path = LITERAL("/Provider.json");
        path = concat(2, dir, path);
        content = readStringFromFile(CSTR(path));
        json = cJSON_Parse(U8_CSTR(content));
        ForEach(cur,json){
            Provider *record = GetData(Provider,cur);
            Database_pushBack(PROVIDER,Data(Provider,record));
        }
        cJSON_Delete(json);
        $STR_BUF(path);
    }
    if(SPEC_KEY == KEY_ESC)
        UI_endScene();
}

int MIprovider_render(int line){
    UI_printMidString(LITERAL("欢迎使用批量增加!"), line);
    line += 1;
    putchar('\n');
    line += 1;
    UI_printMidString(LITERAL("请选择批量增加的内容："), line);
    line += 1;
    putchar('\n');
    line += Menu_render(providerMenu, line);
    return line;
}