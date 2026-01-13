#include "list.h"

/*
    序列划分：将小于分割元素值的元素调至左边，大于的调至右边
    划分过程：
    1. 初始时，i = low，j = high + 1，取list.d[low]为分割元素p
    2. i前进一步，并比较list.d[i]和p，如果前者小于后者，继续前进。否则停止前进。
    3. j前进一步，并比较list.d[j]和p，如果前者大于后者，继续前进。否则停止前进。
    4. 如果i < j，交换list.d[i]和list.d[j]。否则交换list.d[j]和p并退出。
*/
int partition(list *list, int low, int high) {

    int i = low, j = high+1;
    entry pivot = list->d[low]; //分割元素
    do
    {
        do i++; while (i <= high && list->d[i].key < pivot.key);    //i前进
        do j--; while (list->d[j].key > pivot.key);                 //j前进
        if (i < j) swap(list->d, i, j);     // 交换元素
    } while (i < j);
    swap(list->d, low, j);
    return j;   //j是分割元素的下标
}

/*
    快速排序算法的递归过程：
    1. 如果待排序序列中元素数量小等于1，退出排序
    2. 选择待排序序列中的一个元素，其值为d，将待排序序列分成左右两个子序列并满足：
        1) 如果左子序列不空，则其所有元素均小等于d
        2) 如果右子序列不空，则其所有元素均大等于d
    3. 对左子序列进行快速排序
    4. 对右子序列进行快速排序
*/
void quickSort(list* list, int low, int high) {

    int k;
    if(low < high) {    //满足条件表示排序序列至少有两个元素
        k = partition(list, low, high);
        quickSort(list, low, k-1);
        quickSort(list, k+1, high);
    }
}
void quickSort_main(list *list) {
    quickSort(list, 0, list->n-1);
}

//主函数
int main() {
    list list = createExample(10);

    //排序前
    printf("before:\n");
    output(list);

    //排序后
    quickSort_main(&list);
    printf("after:\n");
    output(list);

    return 0;
}