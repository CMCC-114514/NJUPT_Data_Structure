// 顺序搜索

#include <stdio.h>
#include <stdlib.h>
#define notPresent -1

typedef int elemType;

// 顺序表结构体定义
typedef struct SequenceList
{
    int n;              // 表中元素个数
    int length;         // 表的最大长度（超过此长度会发生溢出）
    elemType *element;  // 存储的数据（使用一块连续的地址来存储）
}SequenceList;

#define false 0
#define true 1
typedef int boolean;

// 创建顺序表
boolean init(SequenceList *l, int mSize) {

    l->length = mSize;      // 设置顺序表长度
    l->n = 0;               // 初始情况没有元素
    l->element = (elemType*)malloc(sizeof(elemType) * mSize);   // 生成一维数组空间

    if (!l->element)
    {
        return false;
    }
    return true;
}

// 顺序表顺序搜索（查找元素值，返回元素下标）
int seqSearch(SequenceList l, elemType x) {
    for (int i = 0; i < l.n; i++)
    {
        if (l.element[i] == x)
        {
            return i;
        }
    }
    return notPresent;
}

// 顺序表按下标插入元素
boolean insert(SequenceList *l, int index, elemType x) {

    int i;
    // 下标越界判断和顺序表判满
    if (index < -1 || index > l->length-1 || l->n == l->length)
    {
        return false;
    }
    
    for (i = l->n-1; i > index; i--)    // 从表的最后一个元素开始移动元素
    {
        l->element[i+1] = l->element[i];
    }
    
    l->element[index] = x;    // 将x插入index+1的位置
    l->n++;                     // 元素加一

    return true;
}

// 主函数
int main() {
    SequenceList l;     

    init(&l, 20);       // 创建顺序表l，表的长度为20
    printf("执行了顺序表创建操作, 表的长度是20。");

    printf("\n插入了10个元素: ");
    for (int i = 9; i >= 0; i--)    // 依次插入10个元素
    {
        insert(&l, 9-i, i);
        printf("%4d", i);
    }

    printf("\n顺序搜索序列: ");
    for (int i = 0; i < l.n; i++)
    {
        printf("%4d", seqSearch(l, i));
    }
    
    return 0;
}