//
// Created by guyis on 2019/4/16.
//

#ifndef FRESHMAN_PROJ_C_RECORDINPUT_H
#define FRESHMAN_PROJ_C_RECORDINPUT_H

#include "../../util/Time.h"
#include "../../model/Insert.h"

#define SCENE_RECORD_INPUT 7

extern RecordParam CUR_REC_PARAM;

void RecordInput_init(RecordParam nowVal);

void RecordInput_inLoop();

int RecordInput_render(int);

RecordParam RecordInput_result();

#endif //FRESHMAN_PROJ_C_RECORDINPUT_H
