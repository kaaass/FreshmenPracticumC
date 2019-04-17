//
// Created by guyis on 2019/4/14.
//

#ifndef FRESHMAN_PROJ_C_APPENDORDER_H
#define FRESHMAN_PROJ_C_APPENDORDER_H

#define SCENE_APPEND_ORDER 4
#define SCENE_SELECT_ORDER_TYPE 5

/*
 * 订单增加主视图
 */

void AppendOrder_init();

void AppendOrder_inLoop();

int AppendOrder_render(int);

/*
 * 订单类型选择视图
 */

void SelectOrderType_init();

void SelectOrderType_inLoop();

int SelectOrderType_render(int);

#endif //FRESHMAN_PROJ_C_APPENDORDER_H
