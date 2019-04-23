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
#include "../../model/Insert.h"

#define MENU_CNT 5

Menu *miMenu;

void updatePrint();

void processGuest();

void processProvider();

void processMountings();

void processSelling();

void processPurchase();

void MassIncrease_init() {
    READ_SPEC = true;
    stringbuf name[] = {
            STR_BUF("     客  户 "),
            STR_BUF("    供 货 商"),
            STR_BUF("    零 部 件"),
            STR_BUF("    销售记录"),
            STR_BUF("    进货记录")
    };
    miMenu = Menu_create(-1, 3, name, MENU_CNT, 0);
    UI_startScene(SCENE_MASSINCREASE, STR_BUF("批量增加"));
}

void MassIncrease_inLoop() {
    Menu_inLoop(miMenu);
    if (READ_SPEC) {
        updatePrint();
        if (SPEC_KEY == KEY_ENTER) {
            switch (miMenu->cur) {
                case 0:
                    processGuest();
                    break;
                case 1:
                    processProvider();
                    break;
                case 2:
                    processMountings();
                    break;
                case 3:
                    processSelling();
                    break;
                case 4:
                    processPurchase();
                    break;
                default:
                    break;
            }
        }
        if (SPEC_KEY == KEY_ESC) {
            UI_endScene();
        }
    }
}

void processPurchase() {
    stringbuf dir = UI_inputString(LITERAL("请输入文件路径："));
    cJSON *json;
    stringbuf content;
    List *records = Create(RecordParam);
    Guest object = {.id = -1};
    stringbuf info = $init$;
    double total = 0;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        UI_setFooterUpdate(LITERAL("文件不存在！"));
        return;
    }
    // 读入文件
    content = readStringFromFile(CSTR(dir));
    json = cJSON_Parse(U8_CSTR(content));
    // 读入临时数据库
    Database *purchases = Create(PurchaseRecord);
    if (!DeserializeDB(PurchaseRecord, purchases, json)) {
        UI_setFooterUpdate(LITERAL("文件格式不正确！"));
        return;
    }
    ForEach(cur, purchases) {
        PurchaseRecord *record = GetData(PurchaseRecord, cur);
        RecordParam data = {
                .partId = record->partId,
                .price = record->price,
                .amount = record->amount,
                .total = record->total,
                .time = record->time
        };
        Database_pushBack(records, Data(RecordParam, &data));
        total += record->total;
        // 更新客户
        if (object.id < 1) {
            Provider *seller = GetById(Provider, PROVIDER, record->sellerId);
            object.id = seller->id;
            object.name = seller->name;
            object.phone = seller->phone;
        }
    }
    if (!Insert_checkForAppend(records, object, ORDER_PURCHASE, total, &info)) {
        UI_setFooterUpdate(concat(2, LITERAL("导入数据错误！"), info));
        return;
    }
    Insert_appendOrderLogic(records, object, ORDER_PURCHASE);
    //
    cJSON_Delete(json);
    UI_setFooterUpdate(LITERAL("导入成功！"));
}

void processSelling() {
    stringbuf dir = UI_inputString(LITERAL("请输入文件路径："));
    cJSON *json;
    stringbuf content;
    List *records = Create(RecordParam);
    Guest object = {.id = -1};
    stringbuf info = $init$;
    double total = 0;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        UI_setFooterUpdate(LITERAL("文件不存在！"));
        return;
    }
    // 读入文件
    content = readStringFromFile(CSTR(dir));
    json = cJSON_Parse(U8_CSTR(content));
    // 读入临时数据库
    Database *selling = Create(SellingRecord);
    if (!DeserializeDB(SellingRecord, selling, json)) {
        UI_setFooterUpdate(LITERAL("文件格式不正确！"));
        return;
    }
    ForEach(cur, selling) {
        SellingRecord *record = GetData(SellingRecord, cur);
        RecordParam data = {
                .partId = record->partId,
                .price = record->price,
                .amount = record->amount,
                .total = record->total,
                .time = record->time
        };
        Database_pushBack(records, Data(RecordParam, &data));
        total += record->total;
        // 更新客户
        if (object.id < 1) {
            Guest *guest = GetById(Guest, GUEST, record->guestId);
            object = *guest;
        }
    }
    if (!Insert_checkForAppend(records, object, ORDER_WHOLE_SALE, total, &info)) {
        UI_setFooterUpdate(concat(2, LITERAL("导入数据错误！"), info));
        return;
    }
    Insert_appendOrderLogic(records, object, ORDER_WHOLE_SALE);
    //
    cJSON_Delete(json);
    UI_setFooterUpdate(LITERAL("导入成功！"));
}

void processGuest() {
    stringbuf dir = UI_inputString(LITERAL("请输入文件路径："));
    cJSON *json;
    stringbuf content;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        UI_setFooterUpdate(LITERAL("文件不存在！"));
        return;
    }
    // 读入文件
    content = readStringFromFile(CSTR(dir));
    json = cJSON_Parse(U8_CSTR(content));
    // 写数据库
    Database *guests = Create(Guest);
    if (!DeserializeDB(Guest, guests, json)) {
        UI_setFooterUpdate(LITERAL("文件格式不正确！"));
        return;
    }
    ForEach(cur, guests) {
        Guest *record = GetData(Guest, cur);
        Database_pushBack(GUEST, Data(Guest, record));
    }
    cJSON_Delete(json);
    UI_setFooterUpdate(LITERAL("导入成功！"));
}

void processProvider() {
    stringbuf dir = UI_inputString(LITERAL("请输入文件路径："));
    cJSON *json;
    stringbuf content;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        UI_setFooterUpdate(LITERAL("文件不存在！"));
        return;
    }
    // 读入文件
    content = readStringFromFile(CSTR(dir));
    json = cJSON_Parse(U8_CSTR(content));
    // 写数据库
    Database *providers = Create(Provider);
    if (!DeserializeDB(Provider, providers, json)) {
        UI_setFooterUpdate(LITERAL("文件格式不正确！"));
        return;
    }
    ForEach(cur, providers) {
        Provider *record = GetData(Provider, cur);
        Database_pushBack(PROVIDER, Data(Provider, record));
    }
    cJSON_Delete(json);
    UI_setFooterUpdate(LITERAL("导入成功！"));
}

void processMountings() {
    stringbuf dir = UI_inputString(LITERAL("请输入文件路径："));
    cJSON *json;
    stringbuf content;
    // 检测文件存在
    if (!isExist(CSTR(dir))) {
        UI_setFooterUpdate(LITERAL("文件不存在！"));
        return;
    }
    // 读入文件
    content = readStringFromFile(CSTR(dir));
    json = cJSON_Parse(U8_CSTR(content));
    // 写数据库
    Database *mountings = Create(Mountings);
    if (!DeserializeDB(Mountings, mountings, json)) {
        UI_setFooterUpdate(LITERAL("文件格式不正确！"));
        return;
    }
    ForEach(cur, mountings) {
        Mountings *record = GetData(Mountings, cur);
        Database_pushBack(MOUNTINGS, Data(Mountings, record));
    }
    cJSON_Delete(json);
    UI_setFooterUpdate(LITERAL("导入成功！"));
}

int MassIncrease_render(int line) {
    UI_printMidString(LITERAL("欢迎使用批量增加!"), line++);
    line += 1;
    UI_printMidString(LITERAL("请选择批量增加的内容（按Esc键返回上一页）："), line++);
    line += Menu_render(miMenu, line);
    updatePrint();
    return line;
}

void updatePrint() {
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
