//
// Created by guyis on 2019/4/20.
//

#include "ChooseMountingsType.h"
#include "../Menu.h"
#include "../../data/TableMountings.h"
#include "../UI.h"

enum MountingsType CUR_MOUNTINGS_TYPE = -1;
bool hasResult = false;

Menu *chooseTypeMenu;

void ChooseMountingsType_init(enum MountingsType type) {
    /*
     * 初始化菜单
     */
    stringbuf menuName[] = {
            Mountings_getTypeString(MOUNTINGS_MOUSE),
            Mountings_getTypeString(MOUNTINGS_KEYBOARD),
            Mountings_getTypeString(MOUNTINGS_MEMORY),
            Mountings_getTypeString(MOUNTINGS_GRAPHICS_CARD),
            Mountings_getTypeString(MOUNTINGS_HARD_DISK),
            Mountings_getTypeString(MOUNTINGS_CPU),
            Mountings_getTypeString(MOUNTINGS_SCREEN)
    };
    chooseTypeMenu = Menu_create(-1, 8, menuName, 7, type);
    /*
     * 初始化数据
     */
    CUR_MOUNTINGS_TYPE = type;
    hasResult = false;
    //
    UI_setFooterUpdate(LITERAL("按下Enter键以选择"));
    UI_startScene(SCENE_CHOOSE_MOUNTINGS_TYPE, STR_BUF("选择零配件类型"));
}

void ChooseMountingsType_inLoop() {
    Menu_inLoop(chooseTypeMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            CUR_MOUNTINGS_TYPE = chooseTypeMenu->cur;
            hasResult = true;
            UI_endScene();
        }
    }
}

int ChooseMountingsType_render(int line) {
    Menu_render(chooseTypeMenu, line);
}

enum MountingsType ChooseMountingsType_result() {
    hasResult = false;
    return CUR_MOUNTINGS_TYPE;
}

bool ChooseMountingsType_hasResult() {
    return hasResult;
}