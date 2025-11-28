#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

typedef int elemtype;
//堆栈：先入后出的线性数据结构
typedef struct Stack
{
    int top;                //栈顶下标
    int size;               //栈的大小
    elemtype *elememt;
}Stack;

typedef int boolean;
//创建空堆栈
boolean createStack(Stack *s, int msize) {
    s->size = msize;
    s->top = -1;
    s->elememt = (elemtype*)malloc(sizeof(elemtype) * msize);

    if (!s->elememt)
    {
        return false;
    }
    return true;
}

//销毁堆栈
boolean destroyStack(Stack *s) {
    s->size = 0;
    s->top = -1;
    free(s->elememt);
    return true;
}

//堆栈判空
boolean isEmpty(Stack *s) { return s->top == -1; }

//堆栈判满
boolean isFull(Stack *s) { return s->top == s->size - 1; }

//返回栈顶元素
boolean getTop(Stack *s, elemtype *x) {

    if (isEmpty(s))         //空栈返回false
    {
        return false;   
    }
    
    *x = s->elememt[s->top];
    return true;
}

//元素入栈
boolean pushElement(Stack *s, elemtype x) {

    if (isFull(s))      //满栈返回false
    {
        return false;
    }
    
    s->top++;
    s->elememt[s->top] = x;
    return true;
}

//元素出栈
boolean popElement(Stack *s) {

    if (isEmpty(s))     //空栈返回false
    {
        return false;
    }
    
    s->top--;
    return true;
}

//清除栈中所有元素
void clear(Stack *s) { s->top = -1; }

//主函数
int main() {
    Stack s;
    createStack(&s, 10);

    for (int i = 0; i < 10; i++)    //入栈并输出入栈的元素
    {
        printf("%4d", i);
        pushElement(&s, i);
    }
    printf("\n");
    
    elemtype *x;
    for (size_t i = 0; i <= s.size; i++)    //输出出栈元素
    {
        getTop(&s, x);
        printf("%4d", *x);
        popElement(&s);
    }
    
    destroyStack(&s);

    return 0;
}