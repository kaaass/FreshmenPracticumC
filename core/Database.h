//
// Created by Gu Yue on 2019/3/12.
//

#ifndef FRESHMAN_PROJ_C_DATABASE_H
#define FRESHMAN_PROJ_C_DATABASE_H

#define CheckType(type, obj) ((obj)->dataType == DATA_TYPE_##type)
#define ForEach(i, db) for(Cursor *i=Database_begin(db);i!=NULL;i=Cursor_next(i))
#define GetData(type, obj) ((type *) obj->data)
#define Create(type) Database_create(DATA_TYPE_##type)

/**
 * 链表结点
 */
typedef struct node {
    int dataType; // 存储数据类型的标识
    void *data; // 存储数据
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

/**
 * 创建空数据库
 * @param type 默认结点数据类型
 * @return 数据库
 */
Database *Database_create(int type);

/**
 * 在数据库尾加入节点
 * @param head 数据库
 * @return 数据库
 */
Database *Database_pushBack(Database *head, void *data);

/**
 * 回收数据库所占内存
 * @param head 数据库
 * @return
 */
void Database_destroy(Database *head);

/**
 * 获得数据库的迭代器
 * @param head 数据库
 * @return 迭代器
 */
Cursor *Database_begin(Database *head);

/**
 * 迭代器向后移动
 * @param cursor 迭代器
 * @return 迭代器
 */
Cursor *Cursor_next(Cursor *cursor);

#endif //FRESHMAN_PROJ_C_DATABASE_H