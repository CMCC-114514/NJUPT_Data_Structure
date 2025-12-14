#include "list.h"

/*
    冒泡排序：
    从前向后不断交换相邻次序的数据元素，直到任意相邻数据元素都不再逆序排列
*/
void bubbleSort(list* list) {

    for (int i = list->n-1; i > 0; i--)
    {
        boolean isSwap = false;     //标记一趟排序中是否发生元素交换
        for (int j = 0; j < i; j++)
        {
            if (list->d[j].key > list->d[j+1].key)
            {
                swap(list->d, j, j+1);
                isSwap = true;
            }
            
        }
        if (!isSwap) break;         //如果没有元素交换，则说明排列完成
    }
}

//主函数
int main() {
    list list = createExample(10);

    //排序前
    printf("排序前：\n");
    output(list);

    //排序后
    bubbleSort(&list);
    printf("排序后：\n");
    output(list);

    return 0;
}