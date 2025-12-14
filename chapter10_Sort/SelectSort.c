#include "list.h"

//查找列表中的最小值
int findMin(list list, int startIndex) {
    
    int minIndex = startIndex;
    for (int i = startIndex+1; i < list.n; i++) {
        //从起始下标开始，如果下标i指向的关键字比最小下标指向的关键字还小，那么最小下标就为i
        if (list.d[i].key < list.d[minIndex].key) minIndex = i;
    }
    return minIndex;
}

/*
    简单选择排序步骤：
    第一步：查找待排序序列中关键字最小的元素
    第二步：将最小元素与待排序序列中的第一个元素交换
    第三步：将第一个元素移出下一趟的待排序序列，然后重复此过程，直到待排序序列中只剩下两个元素
*/
void selectSort(list* list) {

    int minIndex, startIndex = 0;
    while (startIndex < list->n-1)
    {
        minIndex = findMin(*list, startIndex);      //第一步
        swap(list->d, startIndex, minIndex);        //第二步
        startIndex++;                               //第三步
    }
}

//主函数
int main() {

    //生成示例列表
    list list = createExample(100);
    
    //输出排序前的表
    printf("排序前：\n");
    output(list);

    //输出排序后的表
    selectSort(&list);
    printf("排序后：\n");
    output(list);

    free(list.d);
    return 0;
}