/*
    编写程序删除单链表中所有关键字值为x的元素
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
boolean delete(chainTable *t, int x) {
    if (t->length == 0)
    {
        printf("链表是空的");
        return false;
    }

    node *n1, *n2;
    n1 = t->head;
    for (int i = 0; i < t->length; i++)
    {
        n2 = n1;        // n2是n1的前驱结点
        n1 = n1->next;  // n1移动
        if (n1->value == x)
        {
            n2->next = n1->next;
        }
    }
    
    return true;
}

// 主函数
int main() {
    chainTable t;

    init(&t);

    for (int i = -1; i < 25; i++)
    {
        if (i % 4 == 0)
        {
            insert(&t, i, -1);
        } else {
            insert(&t, i, i+1);
        }
    }
    
    output(&t);

    delete(&t, -1);

    printf("\n");
    output(&t);
}