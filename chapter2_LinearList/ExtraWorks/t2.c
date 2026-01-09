/*
    编写程序将有序递增的单链表中数据值在a与b（a<=b）之间的元素删除
*/

#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
typedef int boolean;

// 结点结构体
typedef struct node
{
    int value;
    struct node* next;
} node;

// 链表结构体
typedef struct chainTable
{
    node* head;
    int length;
} chainTable;

// 初始化链表
boolean init(chainTable *t) {
    t->head = (node*)malloc(sizeof(node));
    if (!t->head)
    {
        printf("失败");
        return false;
    }
    t->head->next = NULL;   // 设置链表为空表
    t->length = 0;
    return true;
}

// 插入元素
boolean insert(chainTable *t, int i, int x) {

    node *n1, *n2;
    int j;

    if (i < -1 || i > t->length - 1)
    {
        return false;
    }
    
    n1 = t->head;
    for (j = 0; j <= i; j++)
    {
        n1 = n1->next;
    }
    n2 = (node*)malloc(sizeof(node));
    n2->value = x;
    n2->next = n1->next;
    n1->next = n2;
    t->length++;
    return true;
}

// 输出链表
boolean output(chainTable *t) {
    if (t->length == 0)
    {
        printf("链表是空的");
        return false;
    }
    
    node* n = t->head->next;
    while (n)
    {
        printf("%4d", n->value);
        n = n->next;
    }
    return true;
}

// 删除指定内容
boolean delete(chainTable *t, int a, int b) {
    if (t->length == 0)
    {
        printf("链表是空的");
        return false;
    }

    if (a > b)
    {
        printf("要满足a<=b");
        return false;
    }
    
    node *na;
    na = t->head;
    while (na->value < a-1)    // 寻找a的位置
    {
        na = na->next;
    }
    
    node *nb;
    nb = na;
    while (nb->value < b+1)   // 寻找b的位置
    {
        nb = nb->next;
    }
    
    na->next = nb;    // 删除a到b之间的所有结点
    return true;
}

// 主函数
int main() {
    chainTable t;

    init(&t);
    for (int i = -1; i < 15; i++)
    {
        insert(&t, i, i+1);
    }
    
    output(&t);

    delete(&t, 6, 12);
    
    printf("\n");
    output(&t);
}