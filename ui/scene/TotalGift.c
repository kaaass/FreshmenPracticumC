//
// Created by hasee on 2019/4/11.
//

#include <stdio.h>
#include "TotalGift.h"
#include "../UI.h"
#include "Welcome.h"
#include "../UI_Utils.h"
#include "Statistics.h"
#include "../util/Time.h"

void TotalGift_init(){
    READ_SPEC = true;
    UI_setFooterUpdate(LITERAL("按下Enter键以返回..."));
    UI_startScene(SCENE_ABOUT, STR_BUF("礼物总情况"));
}
void TotalGift_inLoop(){
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            // 按下Enter键返回
            UI_endScene();
        }
    }
}

int TotalGift_render(int line){
    UI_printMidString(LITERAL("礼物总情况"), line++);
    putchar('\n'); line += 1;
    printf("    时间                 种类          品牌          数量        客人             手机号              价值   ");
    Database *creat = sort_gift();
    ForEach(cur, creat){
        Present_Situation *record = GetData(Present_Situation,cur);
        Mountings *rec_mountings = GetById(Mountings,MOUNTINGS,record->partId);
        CSTR(Time_toLocalString(record->time_recording));
        printf("    ");
        int selet = (int)record->type;
        switch (selet){
            case 0:
                printf("鼠标");
                printf("")

        }
    }
}