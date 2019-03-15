//
// Created by guyis on 2019/3/12.
//
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Database.h"

const int DATA_TYPE_Header = 0;

/**
 * 创建空数据库
 * @param type 默认结点数据类型
 * @return 数据库
 */
Database *Database_create(int type) {
    Database *db = malloc(sizeof(Database));
    Header *header = malloc(sizeof(Header));

    db->dataType = DATA_TYPE_Header;
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
Database *Database_pushBack(Database *head, void *data, size_t size) {
    DataNode *node = malloc(sizeof(DataNode));
    Header *header = GetData(Header, head);
    void *newData = malloc(size);

    memcpy(newData, data, size);
    node->dataType = header->defaultDataType;
    node->dataSize = size;
    node->data = newData;
    node->next = NULL;
    header->tail->next = node; // 加入链表
    header->tail = node;
    header->cnt++;
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
 * 回收数据库所占内存
 * @param head 数据库
 * @return
 */
void Database_destroy(Database *head) {
    ForEach(cur, head) {
        free(cur->cur);
    }
    free(head->data); // 释放表头信息
    free(head);
}

/**
 * 获得数据库的迭代器
 * @param head 数据库
 * @return 迭代器
 */
Cursor *Database_begin(Database *head) {
    Cursor *cursor;
    DataNode *next;

    // 空表检查
    if (head->next == NULL)
        return NULL;
    next = head->next;
    cursor = malloc(sizeof(Cursor));
    cursor->cur = next;
    cursor->next = next->next;
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

    // 尾节点
    if (cursor->next == NULL)
        return NULL;
    next = cursor->next;
    cursor->cur = next;
    cursor->next = next->next;
    cursor->dataType = next->dataType;
    cursor->dataSize = next->dataSize;
    cursor->data = next->data;
    return cursor;
}