#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int boolean;
#define false 0
#define true 1

// 结点结构体定义
typedef struct node
{
    ElemType value;         // 数据域
    struct node* next;      // 指针域（指向下一个结点）
} node;

// 单链表定义
typedef struct singleList
{
    int length;     // 链表长度
    node* root;     // 根节点
} singleList;

// 单链表初始化
boolean init(singleList* sl) {
    sl->root = NULL;
    sl->length = 0;
    return true;
}

/*
    单链表需要通过每个节点的指针域来访问下一个节点
    不需要事先分配存储整个表的空间，而且插入和删除元素很方便，但代价就是链表断链后会导致数据丢失
    而且在查找元素的时候需要访问目标元素结点的上一个结点（只能顺序读取）
*/

// 单链表查找元素
boolean search(singleList* sl, int index, ElemType* x) {
    node* s;        // 定义搜索结点s

    if (index > sl->length - 1 || index < -1)
    {
        return false;
    }
    
    s = sl->root;   // 从根结点开始，按顺序访问每个结点
    for (int i = 0; i < index; i++)
    {
        s = s->next;    // 访问当前节点的下一个节点
    }
    // 做完这一步，结点s的位置就是目标元素的位置

    *x = s->value;
    return true;
}

// 单链表插入元素
boolean insert(singleList* sl, int index, ElemType x) {
    node *s, *n;        // 定义搜索结点s和新结点n

    if (index < -1 || index > sl->length - 1)
    {
        return false;
    }
    
    s = sl->root;   // 从根结点开始，按顺序访问每个结点
    for (int i = 0; i < index; i++)
    {
        s = s->next;    // 访问当前节点的下一个节点
    }
    // 找到插入位置后，结点s就是插入位置的上一个结点
    
    n = (node*)malloc(sizeof(node));        // 定义插入的新节点n
    n->value = x;       // 即将插入的元素值

    if (index > -1)
    {
        n->next = s->next;      // 将插入位置的下一个结点赋值到新节点上
        s->next = n;            // 将新节点赋值到插入位置的上一个节点上
    } else {
        n->next = sl->root;
        sl->root = n;           // 让新节点n成为头结点
    }

    sl->length++;
    return true;
}

// 单链表删除元素
boolean delete(singleList* sl, int index) {
    node* s1;        // 定义搜索结点s1

    if (index > sl->length - 1 || index < -1)
    {
        return false;
    }
    
    s1 = sl->root;   // 从根结点开始，按顺序访问每个结点
    for (int i = 0; i < index - 1; i++)
    {
        s1 = s1->next;    // 访问当前节点的下一个节点
    }
    // 找到删除位置后，结点s1就是删除位置的上一个结点

    if (index == 0)
    {
        sl->root = sl->root->next;      // 删除头结点
    } else {
        node* s2 = s1->next;    // 定义搜索结点s2，指向删除位置
        s1->next = s2->next;    // 将删除位置的下一个结点赋值给删除位置的上一个结点
    }
    
    sl->length--;
    return true;
}

// 单链表输出
boolean output(singleList* sl) {
    node* s = sl->root;

    if (sl->length == 0) {
        return false;
    }

    while(s) {
        printf("%4d", s->value);
        s = s->next;
    }
    
    return true;
}

// 单链表销毁
boolean destroy(singleList* sl) {
    node* s;
    while (sl->root)
    {
        s = sl->root->next;
        free(sl->root);
        sl->root = s;
    }
    return true;
}

// 主函数
int main() {
    singleList sl;
    init(&sl);
    printf("已将链表初始化\n");

    for (int i = 0; i < 10; i++)
    {
        insert(&sl, i-1, i+1);
    }
    printf("已插入10个元素：");
    output(&sl);

    printf("\n链表的长度是：%d", sl.length);

    delete(&sl, 5);
    printf("\n删除了第5个元素：");
    output(&sl);

    int x;
    search(&sl, 7, &x);
    printf("\n找到了第7个元素，它的值是%d", x);

    destroy(&sl);
    printf("\n销毁了单链表");

    return 0;
}