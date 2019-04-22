//
// Created by guyis on 2019/4/21.
//

#include <cstring_jslike.h>
#include "Settings.h"
#include "../UI.h"

void Settings_init() {
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Esc键以返回..."));
    UI_startScene(SCENE_SETTINGS, STR_BUF("设置"));
}

void Settings_inLoop() {

}

int Settings_render(int line) {

}
