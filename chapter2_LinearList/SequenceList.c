#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

typedef int elemType;
//顺序表定义
typedef struct SequenceList
{
    int n;              //表中元素个数
    int length;         //表长
    elemType *element;  //存储的数据
}SequenceList;

typedef int boolean;
boolean init(SequenceList *l, int mSize) {

    l->length = mSize;      //设置顺序表长度
    l->n = 0;               //初始情况没有元素
    l->element = (elemType*)malloc(sizeof(elemType) * mSize);   //生成一维数组

    if (!l->element)
    {
        return false;
    }
    return true;
}

//顺序表按下标查找元素
boolean search(SequenceList l, int index, elemType *x) {

    if (index > l.length || index < 0)     //下标是否越界
    {
        return false;
    }
    *x = l.element[index];     //没有越界就返回对应元素
    return true;
}

//顺序表按下标插入元素
boolean insert(SequenceList *l, int index, elemType x) {

    //下标越界判断和顺序表判满
    if (index > l->length || index < 0 || l->n == l->length)
    {
        return false;
    }
    
    for (int i = l->n-1; i > index; i--)    //从表的最后一个元素开始移动元素
    {
        l->element[i+1] = l->element[i];
    }
    
    l->element[index+1] = x;    //将x插入index+1的位置
    l->n++;                     //元素加一

    return true;
}

//顺序表按下标删除元素
boolean delete(SequenceList *l, int index) {
    
    //下标越界判断和顺序表判空
    if (index > l->length || index < 0 || l->n == 0)
    {
        return false;
    }
    
    for (int i = index + 1; i < l->n; i++)
    {
        l->element[i-1] = l->element[i];
    }
    l->n--;

    return true;
}

//输出表
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

//顺序表销毁
boolean destroy(SequenceList *l) {
    free(l->element);
    l->n = l->length = 0;
    return true;
}

//主函数
int main() {
    SequenceList l;     //创建顺序表l
    init(&l, 10);

    for (int i = 1; i < 10; i++)    //依次插入10个元素
    {
        insert(&l, i - 1, i);
    }
    output(&l);
    
    delete(&l, 3);      //删除下标为3的元素
    output(&l);

    destroy(&l);
}