#include "list.h"
#include <time.h>

/*
    直接插入排序：
    从只包含一个数据元素的有序序列开始，
    不断地将待排序元素有序插入到这个有序序列中，
    直到有序序列包含了所有待排序元素
*/
void insertSort(list *list) {
    
    int j;
    entry insertItem;   //每一趟的待插入元素
    for (int i = 1; i < list->n; i++)
    {
        insertItem = list->d[i];
        for (j = i-1; j >= 0; j--)
        {
            //将有序序列中的元素向后移动
            if (insertItem.key < list->d[j].key) list->d[j+1] = list->d[j];
            else break;
        }
        list->d[j+1] = insertItem;  //将待插入元素插入有序序列
    }
}

//主函数
int main() {

    clock_t start, end;
    list list = createExample(100);

    //排序前
    printf("before:\n");
    output(list);

    start = clock();
    insertSort(&list);
    end = clock();

    //排序后
    printf("after:\n");
    output(list);

    //输出排序时间
    printf("%lf", (double)(end - start));

    return 0;
}