//
// Created by guyis on 2019/4/20.
//

#ifndef FRESHMAN_PROJ_C_TIMEDURATIONINPUT_H
#define FRESHMAN_PROJ_C_TIMEDURATIONINPUT_H

#include <stdbool.h>
#include "../../util/Time.h"

#define SCENE_TIME_DURATION_INPUT 43

extern Time CUR_TIME_ST;
extern Time CUR_TIME_ED;

void TimeDurationInput_init();

void TimeDurationInput_inLoop();

int TimeDurationInput_render(int);

Time TimeDurationInput_resultSt();

Time TimeDurationInput_resultEd();

bool TimeDurationInput_hasResult();

#endif //FRESHMAN_PROJ_C_TIMEDURATIONINPUT_H
