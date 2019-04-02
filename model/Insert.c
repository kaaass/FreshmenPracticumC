//
// Created by guyis on 2019/3/31.
//

#include <assert.h>
#include "Insert.h"
#include "../data/DataManager.h"
#include "../data/TableGuest.h"
#include "../data/TableProvider.h"

/**
 * 是否存在Guest记录
 * @param name
 * @param phone
 * @return
 */
bool Insert_hasGuest(string name, string phone) {
    bool matchName = empty(name),
            matchPhone = empty(phone);
    ForEach(cur, GUEST) {
        Guest *data = GetData(Guest, cur);
        if ((matchName || EQUAL(name, data->name)) &&
            (matchPhone || EQUAL(phone, data->phone))) {
            return true;
        }
    }
    return false;
}

/**
 * 插入Guest记录
 * @param name
 * @param phone
 */
void Insert_guest(string name, string phone) {
    assert(!empty(name));
    assert(!empty(phone));
    Guest data = {.name = name, .phone = phone};
    Database_pushBack(GUEST, Data(Guest, &data));
}

/**
 * 是否存在Provider记录
 * @param name
 * @param phone
 * @return
 */
bool Insert_hasProvider(string name, string phone) {
    bool matchName = empty(name),
            matchPhone = empty(phone);
    ForEach(cur, PROVIDER) {
        Provider *data = GetData(Provider, cur);
        if ((matchName || EQUAL(name, data->name)) &&
            (matchPhone || EQUAL(phone, data->phone))) {
            return true;
        }
    }
    return false;
}

/**
 * 插入Provider记录
 * @param name
 * @param phone
 */
void Insert_provider(string name, string phone) {

}