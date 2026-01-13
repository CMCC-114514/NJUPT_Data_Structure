/*
    开地址法处理散列冲突
    思想：将具有相同散列地址的同义词元素存储于同一个链表中，
    链表的表头节点地址存储于散列表
*/ 

#include "HashTable.h"

typedef struct node
{
    struct node *next;
    int value;
} node;

