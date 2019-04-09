//
// Created by guyis on 2019/4/8.
//

#include "Welcome.h"
#include "../UI.h"

void Welcome_init() {
    NOW_SCENE = SCENE_WELCOME;
    TITLE = STR_BUF("进销存系统 v1.0");
    BreadCrumb_enter(STR_BUF("首页"));
}