//
// Created by guyis on 2019/4/2.
//

#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_CONFIG_H
#define FRESHMAN_PROJ_C_CONFIG_H

void Config_setString(string key, string value);
stringbuf Config_optString(string key, string defVal);

void Config_setInteger(string key, int value);
int Config_optInteger(string key, int defVal);

#endif //FRESHMAN_PROJ_C_CONFIG_H
