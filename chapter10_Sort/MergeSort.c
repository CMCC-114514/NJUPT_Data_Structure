#include "list.h"

//序列二路合并
void merge(list *list, entry *temp, int low, int n1, int n2) {
    //n1和n2表示长度对应长度的相邻子序列
    int i = low, j = low+n1;    //i和j初始时指向两个序列的第一个元素
    while (i <= low+n1-1 && j <= low+n1+n2-1)
    {
        if (list->d[i].key <= list->d[j].key)
            *temp++ = list->d[i++];
        else *temp++ = list->d[j++];
    }
    while (i <= low+n1-1) *temp++ = list->d[i++];
    while (j <= low+n1+n2-1) *temp = list->d[j++];
}

void mergeSort(list *list) {
    entry temp[MaxSize];
    int low, n1, n2, i, size = 1;
    while (size < list->n)
    {
        low = 0;
        while (low+size < list->n)
        {
            n1 = size;
            if (low+2*size < list->n)
                n2 = size;
            else
                n2 = list->n-low-size;
            merge(list, temp+low, low, n1, n2);
            low += n1 + n2;
        }
        for (i = 0; i<low; i++)
            list->d[i] = temp[i];
        size *= 2;
    }
}

//主函数
int main() {

    list list = createExample(10);

    //排序前
    printf("before:\n");
    output(list);

    //排序后
    mergeSort(&list);
    printf("after:\n");
    output(list);
}