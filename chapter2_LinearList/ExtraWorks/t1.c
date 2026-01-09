/*
    编写程序实现对顺序表逆置
*/

#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define MaxSize 20
typedef int boolean;

// 顺序表结构体，使用整数数组
typedef struct seqList
{
    int* value;
    int n;
    int length;
} seqList;

// 初始化顺序表
boolean init(seqList *l, int maxsize) {
    l->value = (int*)malloc(sizeof(int) * maxsize);

    if (!l->value)      // 生成失败处理
    {
        return false;
    }
    
    l->length = maxsize;
    l->n = 0;
    return true;
}

// 插入元素
boolean insert(seqList *l, int i, int x) {

    // 下标越界判断&顺序表是否充满
    if (i < -1 || i > l->length-1 || l->n == l->length)
    {
        return false;
    }
    
    // 从最后一个元素开始逐个后移元素
    for (int j = l->length-1; j > i; j--)
    {
        l->value[j+1] = l->value[j];
    }
    l->value[i] = x;    // 在位置i插入元素
    l->n++;

    return true;
}

// 输出顺序表
boolean output(seqList l) {
    if (l.length == 0 || l.n == 0)
    {
        printf("顺序表是空的");
        return false;
    }

    for (int i = 0; i < l.n; i++)
    {
        printf("%4d", l.value[i]);
    }
    return true;
}

// 顺序表逆置
boolean reverse(seqList *l) {

    if (l->length == 0 || l->n == 0)
    {
        printf("顺序表是空的");
        return false;
    }

    int temp;
    for (int i = 0; i < l->n/2; i++)
    {
        temp = l->value[i];
        l->value[i] = l->value[l->n-i-1];
        l->value[l->n-i-1] = temp;
    }
    return true;
}

// 主函数
int main() {
    seqList l;

    init(&l, MaxSize);

    for (int i = 0; i < 5; i++)
    {
        insert(&l, i, i);
    }
    
    output(l);

    reverse(&l);

    printf("\n");
    output(l);
}