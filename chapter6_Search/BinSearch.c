// 对半搜索：必须要在有序的顺序表中才可以使用

#include <stdio.h>
#include <stdlib.h>
#define notpresent -1    // 元素不存在


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

// 顺序表的对半查找，输入元素，输出元素下标
int binSearch(SequenceList l, elemType x) {
    int low = 0;
    int high = l.n - 1;
    int mid;
    int count = 0;

    printf("\n搜索的元素为：%d", x);
    printf("\n搜索序列：");
    while (low <= high) {
        count++;
        mid = (low + high) / 2;

        printf("%4d", l.element[mid]);
        if (x < l.element[mid]) {
            high = mid - 1;
        } else if (x > l.element[mid]) {
            low = mid + 1;
        } else {
            printf("\n搜索成功, 元素位置为：%d", mid);
            printf("\n搜索次数为：%d", count);
            return mid;
        }
    }
    
    printf("\n搜索失败");
    printf("\n搜索次数为：%d", count);
    return notpresent;
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
    for (int i = 0; i < l.length; i++)    // 依次插入10个元素
    {
        insert(&l, i, i);
        printf("%4d", i);
    }
    printf("\n\n");

    binSearch(l, 8);        // 搜索成功情况

    printf("\n\n");
    binSearch(l, 11);       // 搜索失败情况
    
    return 0;
}