#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MaxSize 999
typedef int keyType;
typedef char dataType;

#define false 0
#define true 1
typedef int boolean;


//数据元素的顺序存储实现
typedef struct entry
{
    keyType key;
    dataType data;
} entry;
typedef struct list
{
    int n;
    entry d[MaxSize];
} list;

//初始化
void init(list* list) {
    list->n = 0;
}

//插入数据
boolean insert(list* list, keyType k, dataType x) {

    if (list->n == MaxSize) return false;
    list->d[list->n].key = k;
    list->d[list->n].data = x;
    list->n++;
    return true;
}

//输出顺序表
void output(list list) {
    for (int i = 0; i < list.n; i++)
    {
        printf("%d\n", list.d[i].key);
    }
}

//生成示例顺序表：长度为length的随机数表
list createExample(int length) {
    list list;
    init(&list);

    //创建一个长度为length的表
    for (int i = 0; i < length; i++)
    {
        insert(&list, rand(), 'a');
    }

    return list;
}

//交换元素
void swap(entry* d, int i, int j) {

    entry temp;
    if (i == j) return;     //元素相等直接退出

    temp = *(d + i);        //否则交换顺序表中下标为i和下标为j的元素
    *(d + i) = *(d + j);
    *(d + j) = temp;
}