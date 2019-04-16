//
// Created by guyis on 2019/4/2.
//

#include <cJSON.h>
#include "../util/StringUtil.h"

#ifndef FRESHMAN_PROJ_C_CONFIG_H
#define FRESHMAN_PROJ_C_CONFIG_H

void Config_setString(string key, string value);
stringbuf Config_optString(string key, string defVal);

void Config_setInteger(string key, int value);
int Config_optInteger(string key, int defVal);
void Config_setDouble(string key, double value);
double Config_optDouble(string key, double defVal);

void Config_setJson(string key, cJSON *value);
cJSON *Config_getJson(string key);

void Config_setIntArray(string key, int* arr, int n);
int *Config_getIntArray(string key, int *len);

#endif //FRESHMAN_PROJ_C_CONFIG_H
