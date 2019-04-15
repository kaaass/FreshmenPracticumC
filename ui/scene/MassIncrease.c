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

#define MENU_CNT 7

Menu *miMenu;

void updatePrint();
void CreatData_Guest();
void CreatData_Provider();
void CreatData_Mountings();
void CreatData_SellingRecord();
void CreatData_PurchaseRecord();
void CreatData_Order();

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
    UI_startScene(SCENE_MASSINCREASE,STR_BUF("首页>批量增加"));
}

void MassIncrease_inLoop(){
    Menu_inLoop(miMenu);
    if(READ_SPEC){
        updatePrint();
        printf("请输入导入文件的路径：");
        if(SPEC_KEY == KEY_ENTER){
            switch (miMenu->cur) {
                case 0:
                    CreatData_Guest();
                    break;
                case 1:
                    CreatData_Provider();
                    break;
                case 2:
                    CreatData_Mountings();
                    break;
                case 3:
                    CreatData_SellingRecord();
                    break;
                case 4:
                    CreatData_PurchaseRecord();
                    break;
                case 5:
                    CreatData_Order();
                    break;
                case 6:
                    DataManager_save(LITERAL("data"));
                    exit(0);
                default:
                    break;
            }
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

void CreatData_Guest(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // Guest
    path = LITERAL("/Guest.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Guest, GUEST, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}

void CreatData_Provider(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // Provider
    path = LITERAL("/Provider.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Provider, PROVIDER, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}

void CreatData_Mountings(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // Mountings
    path = LITERAL("/Mountings.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Mountings, MOUNTINGS, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}

void CreatData_SellingRecord(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // SellingRecord
    path = LITERAL("/SellingRecord.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(SellingRecord, SELLING_RECORD, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}

void CreatData_PurchaseRecord(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // PurchaseRecord
    path = LITERAL("/PurchaseRecord.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(PurchaseRecord, PURCHASE_RECORD, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}

void CreatData_Order(){
    cJSON *json;
    char Approach[200];
    scanf("%[^\n]",Approach);
    string dir = STRING(Approach);
    stringbuf path, content;
    // 默认数据库创建
    if (!isExist(CSTR(dir))) {
        DataManager_reset();
        DataManager_save(dir);
    }
    // Order
    path = LITERAL("/Order.json");
    path = concat(2, dir, path);
    content = readStringFromFile(CSTR(path));
    json = cJSON_Parse(U8_CSTR(content));
    DeserializeDB(Order, ORDER, json);
    cJSON_Delete(json);
    $STR_BUF(path);
}