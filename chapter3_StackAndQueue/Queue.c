#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

typedef int elemType;
//循环队列结构体定义
typedef struct Queue {
    int front;          //队头
    int rear;           //队尾
    int maxSize;        //队列长度
    elemType *element;  
} queue;

typedef int boolean;
//创建空队列
boolean create (queue *q, int mSize) {
    q->maxSize = mSize;
    q->element = (elemType*)malloc(sizeof(elemType) * mSize);
    q->front = q->rear = 0;
    return true;
}

//销毁队列
boolean destroy(queue *q) {
    q->maxSize = 0;
    q->front = q->rear = 0;
    free(q->element);
    return true;
}

//队列判空
boolean isEmpty(queue *q) { return q->front == q->rear; }

//队列判满
boolean isFull(queue *q) { return (q->rear + 1) % q->maxSize == q->front; }

//获取队头元素
boolean getFront(queue *q, elemType *x) {
    if (isEmpty(q))
    {
        return false;
    }
    *x = q->element[(q->rear + 1) % q->maxSize];
    return true;
}

//元素入队
boolean enQueue(queue *q, elemType x) {
    if (isFull(q))
    {
        return false;
    }
    q->rear = (q->rear + 1) % q->maxSize;
    q->element[q->rear] = x;
    return true;
}

//元素出队
boolean deQueue(queue *q) {
    if (isEmpty(q))
    {
        return false;
    }
    q->front = (q->rear + 1) % q->maxSize;
    return true;
}

//清除元素
void clear(queue *q) { q->front = q->rear = 0; }