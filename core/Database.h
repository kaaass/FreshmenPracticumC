//
// Created by Gu Yue on 2019/3/12.
//
#include <stddef.h>
#include <stdbool.h>

#ifndef FRESHMAN_PROJ_C_DATABASE_H
#define FRESHMAN_PROJ_C_DATABASE_H

#define CheckTypeId(typeId, obj) ((obj)->dataType == typeId)
#define CheckType(type, obj) (CheckTypeId(DATA_TYPE_##type, obj) && (sizeof(type) == (obj)->dataSize))
#define ForEach(i, db) for(Cursor *i=Database_begin(db);i!=NULL;i=Cursor_next(i))
#define GetData(type, obj) ((type *) obj->data)
#define Data(type, obj) (void *) obj,sizeof(type),DATA_TYPE_##type
#define Create(type) Database_create(DATA_TYPE_##type)
#define GetById(type, db, id) ((type *) Database_getById(db,id))
#define Tail(type, db) GetData(type,GetData(Header,db)->tail)

#define ID_LIKE (1 << 5)
#define BASIC_TYPE (1 << 6)

/**
 * 基本数据类型
 */
#define DATA_TYPE_string 1 | BASIC_TYPE
#define DATA_TYPE_int 2 | BASIC_TYPE

/**
 * 链表结点
 */
typedef struct node {
    int dataType; // 存储数据类型的标识
    void *data; // 存储数据
    size_t dataSize; // 存储数据长度
    struct node *next; // 下一节点
} DataNode;

typedef DataNode List; // 别名
typedef DataNode Database; // 别名

/**
 * 游标
 */
typedef struct {
    DataNode *cur; // 当前遍历的结点
    int dataType; // 当前结点的数据类型
    void *data; // 当前结点的数据
    size_t dataSize; // 当前结点的数据长度
    DataNode *prev; // 上一个遍历结点
    DataNode *next; // 下一个待遍历结点
} Cursor;

/**
 * 数据类型：哨兵结点
 */
#define DATA_TYPE_Header 0

typedef struct {
    int cnt;
    int defaultDataType;
    DataNode *tail;
} Header;

/**
 * 鸭子类型：ID
 */
typedef struct {
    int id;
} IdLike;

Database *Database_create(int type);

Database *Database_pushBack(Database *head, void *data, size_t size, int type);

Database *Database_pushBackAutoInc(Database *head, void *data, size_t size, int type, bool autoInc);

Database *Database_pop(Database *head);

size_t Database_size(Database *head);

void Database_destroyItem(DataNode* cur);

void Database_destroy(Database *head);

void Database_clear(Database *head);

Cursor *Database_begin(Database *head);

Cursor *Cursor_next(Cursor *cursor);

bool Cursor_hasNext(Cursor *cursor);

void Database_modifyById(Database *head, int id, void *data, size_t size, int type);

void Database_removeByCursor(Database *db, Cursor *cursor);

Cursor *Database_getCursorById(Database *head, int id);

void *Database_getById(Database *head, int id);

Database *arrayToDatabase(void *arr[], size_t size, int type, size_t length);

#endif //FRESHMAN_PROJ_C_DATABASE_H