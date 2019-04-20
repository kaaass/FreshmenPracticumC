//
// Created by guyis on 2019/4/20.
//

#ifndef FRESHMAN_PROJ_C_CHOOSEMOUNTINGSTYPE_H
#define FRESHMAN_PROJ_C_CHOOSEMOUNTINGSTYPE_H

#include <stdbool.h>

#define SCENE_CHOOSE_MOUNTINGS_TYPE 42

extern enum MountingsType CUR_MOUNTINGS_TYPE;

void ChooseMountingsType_init(enum MountingsType type);

void ChooseMountingsType_inLoop();

int ChooseMountingsType_render(int);

enum MountingsType ChooseMountingsType_result();

bool ChooseMountingsType_hasResult();

#endif //FRESHMAN_PROJ_C_CHOOSEMOUNTINGSTYPE_H
