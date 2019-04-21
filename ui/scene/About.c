//
// Created by guyis on 2019/4/10.
//

#include <stdio.h>
#include "About.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"

void About_init() {
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Esc键以返回..."));
    UI_startScene(SCENE_ABOUT, STR_BUF("关于"));
}

void About_inLoop() {
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ESC) {
            // 按下Esc键返回
            UI_endScene();
        }
    }
}

int About_render(int line) {
    UI_printMidString(LITERAL("关  于"), line++);
    putchar('\n'); line += 1;
    UI_printMidString(LITERAL("本程序为程序设计基础课程设计项目 (2018级)的实现。"), line++);
    putchar('\n'); line += 1;
    UI_printMidString(LITERAL("小组成员为（排名不分先后，括号内为GitHub账户）："), line++);
    UI_printMidString(LITERAL("谷越（@KAAAsS）"), line++);
    UI_printMidString(LITERAL("吴非凡（@KveinAxel）"), line++);
    UI_printMidString(LITERAL("杜浩贤（@soobright）"), line++);
    UI_printMidString(LITERAL("吕民轩（@XuanLaoYee）"), line++);
    putchar('\n'); line += 1;
    UI_printMidString(LITERAL("特别鸣谢："), line++);
    UI_printMidString(LITERAL("GitHub - 代码仓库托管"), line++);
    UI_printMidString(LITERAL("cJson - Json数据解析"), line++);
    UI_printMidString(LITERAL("Unity - 单元测试框架"), line++);
    UI_printMidString(LITERAL("Travis CI - 自动化单元测试"), line++);
    UI_printMidString(LITERAL("cmake-unity-tutorial - CMake配置"), line++);
    UI_printMidString(LITERAL("CMake-codecov - 代码覆盖率测试"), line++);
    return line;
}
