#include <stdio.h>
#include <stdlib.h>
#define overflow 2      // 元素上溢
#define underflow 3     // 元素下溢
#define notpresent 4    // 元素不存在
#define duplicate 5     // 元素重复

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

// 顺序表按下标查找元素，返回元素值
boolean search(SequenceList l, int index, elemType *x) {

    if (index > l.length || index < 0)     // 下标是否越界
    {
        return false;
    }
    *x = l.element[index];     // 没有越界就返回对应元素
    return true;
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

// 顺序表按下标删除元素
boolean delete(SequenceList *l, int index) {
    
    // 下标越界判断和顺序表判空
    if (index > l->length || index < 0 || l->n == 0)
    {
        return false;
    }
    
    for (int i = index + 1; i < l->n; i++)      // 删除元素后，从前向后移动元素
    {
        l->element[i-1] = l->element[i];
    }
    l->n--;

    return true;
}

// 输出顺序表中的元素
void output(SequenceList *l) {

    if (l->n == 0)
    {
        printf("这个表是空的");
    }
    
    for (int i = 1; i < l->n; i++)
    {
        printf("%4d", l->element[i]);
    }
    printf("\n");
}

// 顺序表销毁（释放空间）
boolean destroy(SequenceList *l) {
    free(l->element);
    l->n = l->length = 0;
    return true;
}

// 主函数
int main() {
    SequenceList l;     

    init(&l, 20);       // 创建顺序表l，表的长度为10
    printf("执行了顺序表创建操作, 表的长度是20。");

    for (int i = 0; i < 10; i++)    // 依次插入10个元素
    {
        insert(&l, i-1, i);
    }
    printf("\n插入了10个元素: ");
    output(&l);
    
    delete(&l, 3);      //删除下标为3的元素
    printf("删除了下标为3的元素: ");
    output(&l);

    elemType x = -1;
    int i = 10;
    boolean flag = search(l, i, &x);
    printf("%s下标为%d的元素, 它的值是%d。", flag?"找到了":"没有找到", i, x);

    destroy(&l);
    printf("\n将顺序表销毁了。");
}