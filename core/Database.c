//
// Created by guyis on 2019/3/12.
//
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Database.h"
#include "../util/MemoryUtil.h"
#include "../data/TableConfig.h"
#include "../data/TableGuest.h"
#include "../data/TableMountings.h"
#include "../data/TableProvider.h"

/**
 * 创建空数据库
 * @param type 默认结点数据类型
 * @return 数据库
 */
Database *Database_create(int type) {
    Database *db = MALLOC(Database);
    Header *header = MALLOC(Header);

    db->dataType = DATA_TYPE_Header;
    db->dataSize = sizeof(Header);
    header->cnt = 0;
    header->defaultDataType = type;
    header->tail = db;
    db->data = header;
    db->next = NULL;
    return db;
}

/**
 * 在数据库尾加入节点
 * @param head 数据库
 * @param data 使用Data宏进行数据组织
 * @return 数据库
 */
Database *Database_pushBack(Database *head, void *data, size_t size, int type) {
    return Database_pushBackAutoInc(head, data, size, type, true);
}

/**
 * 在数据库尾加入节点，允许自动增加id字段
 * @param head 数据库
 * @param data 使用Data宏进行数据组织
 * @param autoInc 是否自动增加
 * @return 数据库
 */
Database *Database_pushBackAutoInc(Database *head, void *data, size_t size, int type, bool autoInc) {
    DataNode *node;
    Header *header;
    void *newData;

    assert(head);
    node = MALLOC(DataNode);
    header = GetData(Header, head);
    assert(type == header->defaultDataType);
    newData = malloc(size);
    memcpy(newData, data, size);
    node->dataType = header->defaultDataType;
    node->dataSize = size;
    node->data = newData;
    node->next = NULL;
    header->tail->next = node; // 加入链表
    header->tail = node;
    header->cnt++;

    // ID自增
    if ((type & ID_LIKE) && autoInc) {
        IdLike *idNode = GetData(IdLike, node);
        idNode->id = header->cnt;
    }

    return head;
}

/**
 * 删除数据库最后一条记录
 * @param head
 * @return
 */
Database *Database_pop(Database *head) {
    Header *header;
    DataNode *cur;

    assert(head);
    header = GetData(Header, head);
    if (header->cnt < 1)
        return head;
    cur = head;
    while (cur->next != NULL && cur->next->next != NULL) {
        cur = cur->next;
    }
    Database_destroyItem(cur->next, false);
    cur->next = NULL;
    header->tail = cur;
    header->cnt--;
    return head;
}

/**
 * 返回数据库记录数
 * @param head 数据库
 * @return 记录数
 */
size_t Database_size(Database *head) {
    size_t size = 0;

    if (head != NULL) {
        Header *header = GetData(Header, head);
        assert(header);
        size = (size_t) header->cnt;
        assert(size >= 0);
    }
    return size;
}

/**
 * 释放链表结点
 * @param cur
 */
void Database_destroyItem(DataNode *cur, bool protectNode) {
    if (cur == NULL)
        return;
    // 释放字符串
    switch (cur->dataType) { // TODO: 增加UI表格的释放
        case DATA_TYPE_Config:;
            Config *config = GetData(Config, cur);
            $STR_BUF(config->key);
            $STR_BUF(config->value);
            break;
        case DATA_TYPE_Guest:;
            Guest *guest = GetData(Guest, cur);
            $STR_BUF(guest->name);
            $STR_BUF(guest->phone);
            break;
        case DATA_TYPE_Mountings:;
            Mountings *mountings = GetData(Mountings, cur);
            $STR_BUF(mountings->name);
            break;
        case DATA_TYPE_Provider:;
            Provider *provider = GetData(Provider, cur);
            $STR_BUF(provider->name);
            $STR_BUF(provider->phone);
            break;
        default:
            break;
    }
    if (protectNode) {
        cur->data = NULL;
    } else {
        free(cur);
    }
}

/**
 * 回收数据库所占内存
 * @param head 数据库
 * @return
 */
void Database_destroy(Database *head) {
    assert(head);
    ForEach(cur, head) {
        Database_destroyItem(cur->cur, false);
    }
    free(head->data); // 释放表头信息
    free(head);
}

/**
 * 清空数据库内容
 * @param head
 */
void Database_clear(Database *head) {
    Header *header = GetData(Header, head);
    ForEach(cur, head) {
        Database_destroyItem(cur->cur, false);
    }
    header->cnt = 0;
    header->tail = head;
    head->next = NULL;
}

/**
 * 获得数据库的迭代器
 * @param head 数据库
 * @return 迭代器
 */
Cursor *Database_begin(Database *head) {
    Cursor *cursor;
    DataNode *next;

    assert(head);
    // 空表检查
    if (head->next == NULL)
        return NULL;
    next = head->next;
    cursor = MALLOC(Cursor);
    cursor->cur = next;
    cursor->next = next->next;
    cursor->prev = head;
    cursor->dataType = next->dataType;
    cursor->dataSize = next->dataSize;
    cursor->data = next->data;
    return cursor;
}

/**
 * 迭代器向后移动
 * @param cursor 迭代器
 * @return 迭代器
 */
Cursor *Cursor_next(Cursor *cursor) {
    DataNode *next;

    assert(cursor);
    // 尾节点
    if (Cursor_hasNext(cursor))
        return NULL;
    next = cursor->next;
    cursor->prev = cursor->cur;
    cursor->cur = next;
    cursor->next = next->next;
    cursor->dataType = next->dataType;
    cursor->dataSize = next->dataSize;
    cursor->data = next->data;
    return cursor;
}

/**
 * 迭代器是否有下一节点
 * @param cursor
 * @return
 */
bool Cursor_hasNext(Cursor *cursor) {
    assert(cursor);
    if (cursor->next == NULL)
        return true;
    return false;
}

/**
 * 删除数据库项目并释放内存
 * @param cursor
 */
void Database_removeByCursor(Database *db, Cursor *cursor) {
    assert(cursor);
    assert(cursor->prev);
    Database_destroyItem(cursor->cur, false);
    cursor->prev->next = cursor->next;
    Header *header = GetData(Header, db);
    header->cnt--;
    if (cursor->next == NULL) {
        header->tail = cursor->prev;
    }
}

/**
 * 由ID修改数据库对应结点的内容
 * @param head
 * @param id
 * @param data
 * @return
 */
void Database_modifyById(Database *head, int id, void *data, size_t size, int type) {
    assert(head);
    assert(id ^ ID_LIKE);
    Cursor *cur = Database_getCursorById(head, id);
    if (cur == NULL)
        return;
    DataNode *node = MALLOC(DataNode);
    void *newData = malloc(size);
    memcpy(newData, data, size);
    // 分配ID
    IdLike *idLike = newData;
    idLike->id = ((IdLike *) cur->data)->id;
    // 删除旧结点
    Database_destroyItem(cur->cur, true);
    // 更换新节点
    cur->cur->data = newData;
}

/**
 * 由ID获得数据库对应节点的迭代器
 * @param head
 * @param id
 * @return
 */
Cursor *Database_getCursorById(Database *head, int id) {
    assert(head);
    assert(id ^ ID_LIKE);
    ForEach(cur, head) {
        IdLike *node = GetData(IdLike, cur);
        if (node->id == id) {
            return cur;
        }
    }
    return NULL;
}

/**
 * 由ID获得数据库对应节点
 * @param head
 * @param id
 * @return
 */
void *Database_getById(Database *head, int id) {
    Cursor *cur = Database_getCursorById(head, id);
    if (cur == NULL)
        return NULL;
    return cur->data;
}

/**
 * 将指针数组转为链表
 *
 * 注意：指针数组指向内容将会被复制，id将会重排
 * @param arr 使用Data宏，传入一个指针数组
 * @param size 使用Data宏
 * @param type 使用Data宏
 * @param length 数组元素个数
 * @return
 */
Database *arrayToDatabase(void *arr[], size_t size, int type, size_t length) {
    Database *db = Database_create(type);
    for (int i = 0; i < length; i++) {
        Database_pushBackAutoInc(db, arr[i], size, type, false);
    }
    return db;
}