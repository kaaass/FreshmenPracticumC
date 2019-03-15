//
// Created by Gu Yue on 2019/3/12.
//

#ifndef FRESHMAN_PROJ_C_DATABASE_H
#define FRESHMAN_PROJ_C_DATABASE_H

#define CheckType(type, obj) ((obj)->dataType == DATA_TYPE_##type && sizeof(type) == (obj)->dataSize)
#define ForEach(i, db) for(Cursor *i=Database_begin(db);i!=NULL;i=Cursor_next(i))
#define GetData(type, obj) ((type *) obj->data)
#define Data(type, obj) (void *) obj,sizeof(type)
#define Create(type) Database_create(DATA_TYPE_##type)

/**
 * 链表结点
 */
typedef struct node {
    int dataType; // 存储数据类型的标识
    void *data; // 存储数据
    size_t dataSize; // 存储数据长度
    struct node *next; // 下一节点
} DataNode;

typedef DataNode Database; // 别名

/**
 * 游标
 */
typedef struct {
    DataNode *cur; // 当前遍历的结点
    int dataType; // 当前结点的数据类型
    void *data; // 当前结点的数据
    size_t dataSize; // 当前结点的数据长度
    DataNode *next; // 下一个待遍历结点
} Cursor;

/**
 * 数据类型：哨兵结点
 */
const int DATA_TYPE_Header;

typedef struct {
    int cnt;
    int defaultDataType;
    DataNode *tail;
} Header;

Database *Database_create(int type);

Database *Database_pushBack(Database *head, void *data, size_t size);

size_t Database_size(Database *head);

void Database_destroy(Database *head);

Cursor *Database_begin(Database *head);

Cursor *Cursor_next(Cursor *cursor);

#endif //FRESHMAN_PROJ_C_DATABASE_H