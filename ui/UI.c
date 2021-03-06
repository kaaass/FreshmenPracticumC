//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include "UI_Utils.h"
#include "UI.h"
#include "scene/Welcome.h"
#include "scene/About.h"
#include "scene/View.h"
#include "scene/AppendOrder.h"
#include "scene/ChooseGuest.h"
#include "scene/RecordInput.h"
#include "scene/StatisticsSituation.h"
#include "scene/TotalGift.h"
#include "scene/Profit.h"
#include "scene/Singleitem.h"
#include "scene/MassIncrease.h"
#include "scene/Inventory.h"
#include "scene/ViewPurchase.h"
#include "scene/ViewSell.h"
#include "scene/ChooseMountingsType.h"
#include "scene/TimeDurationInput.h"
#include "scene/Settings.h"

#define COLOR_FOOTER 0x07

List *BREAD_CRUMB;
List *SCENE_STACK;
stringbuf FOOTER;
int NOW_SCENE;
bool READ_SPEC;
int SPEC_KEY = 0;

void UI_init() {
    BREAD_CRUMB = Create(string);
    SCENE_STACK = Create(int);
    FOOTER = $init$;
    // 默认场景
    Welcome_init();
}

bool UI_runSceneLoop() {
    switch (NOW_SCENE) {
        case SCENE_WELCOME:
            Welcome_inLoop();
            break;
        case SCENE_ABOUT:
            About_inLoop();
            break;
        case SCENE_VIEW:
            View_inLoop();
            break;
        case SCENE_VIEW_PURCHASE:
            ViewPurchase_inLoop();
            break;
        case SCENE_VIEW_SELL:
            ViewSell_inLoop();
            break;
        case SCENE_CHOOSE_MOUNTINGS_TYPE:
            ChooseMountingsType_inLoop();
            break;
        case SCENE_TIME_DURATION_INPUT:
            TimeDurationInput_inLoop();
            break;
        case SCENE_APPEND_ORDER:
            AppendOrder_inLoop();
            break;
        case SCENE_SELECT_ORDER_TYPE:
            SelectOrderType_inLoop();
            break;
        case SCENE_CHOOSE_GUEST:
            ChooseGuest_inLoop();
            break;
        case SCENE_RECORD_INPUT:
            RecordInput_inLoop();
            break;
        case SCENE_STATISTICS_SITUATION:
            StatisticsSituation_inLoop();
            break;
        case SCENE_PROFIT_SITUATION:
            Profit_inLoop();
            break;
        case SCENE_TOTAL_GIFT:
            TotalGift_inLoop();
            break;
        case SCENE_SINGLEITEM:
            Singleitem_inLoop();
            break;
        case SCENE_MASSINCREASE:
            MassIncrease_inLoop();
            break;
        case SCENE_INVENTORY:
            Inventory_inLoop();
            break;
        case SCENE_SETTINGS:
            Settings_inLoop();
            break;
        default:
            return false;
    }
    return true;
}

void UI_mainLoop() {
    UI_init();
    UI_render();
    while (true) {
        UI_setCursorVisible(!READ_SPEC);
        UI_getSpecKey();
        if (!UI_runSceneLoop())
            break;
    }
}

int UI_renderBreadCrumb() {
    ForEach(cur, BREAD_CRUMB) {
        printf(" %s > ", CSTR(*GetData(string, cur)));
    }
    putchar('\n');
    for (int i = 0; i < CON_WIDTH; i++) putchar('-');
    return 2;
}

int UI_renderScene(int line) {
    switch (NOW_SCENE) {
        case SCENE_WELCOME:
            return Welcome_render(line);
        case SCENE_ABOUT:
            return About_render(line);
        case SCENE_VIEW:
            return View_render(line);
        case SCENE_VIEW_PURCHASE:
            return ViewPurchase_render(line);
        case SCENE_VIEW_SELL:
            return ViewSell_render(line);
        case SCENE_CHOOSE_MOUNTINGS_TYPE:
            return ChooseMountingsType_render(line);
        case SCENE_TIME_DURATION_INPUT:
            return TimeDurationInput_render(line);
        case SCENE_APPEND_ORDER:
            return AppendOrder_render(line);
        case SCENE_SELECT_ORDER_TYPE:
            return SelectOrderType_render(line);
        case SCENE_CHOOSE_GUEST:
            return ChooseGuest_render(line);
        case SCENE_RECORD_INPUT:
            return RecordInput_render(line);
        case SCENE_STATISTICS_SITUATION:
            return StatisticsSituation_render(line);
        case SCENE_PROFIT_SITUATION:
            return Profit_render(line);
        case SCENE_TOTAL_GIFT:
            return  TotalGift_render(line);
        case SCENE_SINGLEITEM:
            return Singleitem_render(line);
        case SCENE_MASSINCREASE:
            return MassIncrease_render(line);
        case SCENE_INVENTORY:
            return Inventory_render(line);
        case SCENE_SETTINGS:
            return Settings_render(line);
            // 注册
        default:
            return 0;
    }
}

int UI_renderFooter() {
    UI_setTextColor(COLOR_FOOTER);
    UI_moveCursor((Position) {0, CON_HEIGHT - 1});
    printf("%s", CSTR(FOOTER));
    UI_setTextColor(COLOR_DEF);
    Position org = UI_getCursorPos();
    int clearCnt = (int) (CON_WIDTH - UI_stringWidth(FOOTER));
    while (clearCnt--) putchar(' ');
    UI_moveCursor(org);
    return 1;
}

void UI_render() {
    int lineCnt = 0;
    // 重绘
    system("cls");
    // 面包屑
    lineCnt += UI_renderBreadCrumb();
    // 场景
    UI_renderScene(lineCnt);
    // 页脚
    UI_renderFooter();
}

/**
 * 读取特殊键键值
 * @return
 */
void UI_getSpecKey() {
    if (READ_SPEC) {
        SPEC_KEY = 0;
        int key = getch();
        if (key == KEY_SIG) {
            SPEC_KEY = getch();
        } else {
            SPEC_KEY = key;
        }
    }
}

/**
 * 设置页脚
 * @param footer 传入字面字符串常量
 */
void UI_setFooterUpdate(string footer) {
    if (footer == NULL)
        return;
    freeAssign(&FOOTER, cloneString(footer));
    UI_renderFooter();
}

/**
 * 进入场景（初始化最后调用）
 * @param sceneId
 * @param title
 */
void UI_startScene(int sceneId, string title) {
    NOW_SCENE = sceneId;
    BreadCrumb_enter(title);
    Database_pushBack(SCENE_STACK, Data(int, &NOW_SCENE));
    UI_render();
}

/**
 * 退出当前场景
 */
void UI_endScene() {
    BreadCrumb_exit();
    Database_pop(SCENE_STACK);
    NOW_SCENE = *Tail(int, SCENE_STACK);
    UI_render();
}

void UI_title(string name) {
    stringbuf title = concat(2, name, LITERAL(" - 进销存系统 v1.0"));
    UI_setTitle(title);
    $STR_BUF(title);
}

void BreadCrumb_enter(string name) {
    // 更新标题
    UI_title(name);
    // 插入面包屑
    Database_pushBack(BREAD_CRUMB, Data(string, &name));
}

void BreadCrumb_exit() {
    Database_pop(BREAD_CRUMB);
    UI_title(*Tail(string , BREAD_CRUMB));
}