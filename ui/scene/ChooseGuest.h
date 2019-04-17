//
// Created by guyis on 2019/4/14.
//

#ifndef FRESHMAN_PROJ_C_CHOOSEGUEST_H
#define FRESHMAN_PROJ_C_CHOOSEGUEST_H

#include "../../data/TableGuest.h"

#define SCENE_CHOOSE_GUEST 6

extern Guest CUR_GUEST;

void ChooseGuest_init(int guestId, int type);

void ChooseGuest_inLoop();

int ChooseGuest_render(int);

Guest ChooseGuest_result();

#endif //FRESHMAN_PROJ_C_CHOOSEGUEST_H
