/*
    堆排序：
    将序列存入最大堆（或最小堆），输出堆顶元素，然后将输出元素后的堆调整成最大堆（最小堆）
    直到所有的元素都被输出
*/

#include <stdio.h>
#include <stdlib.h>

typedef int boolean;
#define false 0
#define true 1

#define MAXSIZE 30

// 最大堆
typedef struct minheap
{
    int n;
    int value[MAXSIZE];
} minheap;

// 最大堆的向下调整
void adjustDown(int value[], int current, int border) {
    int p = current;
    int minChild;
    int temp;

    while (2*p+1 <=border)
    {
        if ((2*p+2 <= border) && (value[2*p+1] > value[2*p+2])) {
            minChild = 2 * p + 2;
        } else {
            minChild = 2 * p + 1;
        }
        
        if (value[p] <= value[minChild]) {
            break;
        } else {
            temp = value[p];
            value[p] = value[minChild];
            value[minChild] = temp;
            p = minChild;
        }
    }
}

// 建堆运算
void create(minheap* heap, int n) {
    for (int i = (n-2)/2; i > -1; i--)
    {
        adjustDown(heap->value, i, n-1);
    }
}

// 添加元素
void append(minheap* heap, int x) {
    if (heap->n == MAXSIZE)
    {
        return;
    }
    
    heap->value[heap->n] = x;
    heap->n++;
}
// 堆排序
void heapSort(minheap* heap) {
    int temp;

    for (int i = (heap->n-2)/2; i >= 0; i--)
    {
        adjustDown(heap->value, i, heap->n-1);
    }
    
    for (int i = heap->n-1; i > 0; i--)
    {
        temp = heap->value[0];
        heap->value[0] = heap->value[i];
        heap->value[i] = temp;
        adjustDown(heap->value, 0, i-1);
    }
}