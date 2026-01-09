#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef int Boolean;
#define false 0
#define true 1

typedef struct Node {
   ElemType element;     //结点的数据域
   struct Node* link;   //结点的指针域
}Node;

typedef struct {
   struct Node* head;    //表头结点
   int n;
}HeaderList;


//带表头结点单链表的初始化
Boolean Init(HeaderList* h) {
   h->head = (Node*)malloc(sizeof(Node));      //生成表头结点
   if (!h->head) {
       return false;
   }
   h->head->link = NULL;                     //设置单链表为空表
   h->n = 0;
   return true;
}


//带表头结点单链表的查找
Boolean Find(HeaderList* h, int i, ElemType* x) {
   Node* p;
   int j;
   if (i<0 || i>h->n - 1) {
       return false;
   }
   p = h->head->link;
   for (j = 0; j < i; j++) {
       p = p->link;
   }
   *x = p->element;
   return true;
}


//带表头结点单链表的插入
Boolean Insert(HeaderList* h, int i, ElemType x) {
   Node* p, * q;
   int j;
   if (i<-1 || i>h->n - 1)
       return false;
   p = h->head;                      //从头结点开始找ai元素所在的结点p
   for (j = 0; j <= i; j++) {
       p = p->link;
   }
   q = (Node*)malloc(sizeof(Node));  //生成新结点q
   q->element = x;
   q->link = p->link;                //新结点q插在p之后
   p->link = q;
   h->n++;
   return true;
}


//带表头结点单链表的删除
Boolean Delete(HeaderList* h, int i) {
   int j;
   Node* p, * q;
   if (!h->n) {
       return false;
       if (i<0 || i>h->n - 1) {
           return false;
       }
   }
   q = h->head;
   for (j = 0; j < i; j++) {
       q = q->link;
   }
   p = q->link;
   q->link = p->link;                //从单链表中删除p所指结点
   free(p);                        //释放p所指结点的存储空间
   h->n--;
   return true;
}


//带表头结点单链表的输出
Boolean Output(HeaderList* h) {
   Node* p;
   if (!h->n)
       return false;
   p = h->head->link;
   while (p) {
       printf("%d ", p->element);
       p = p->link;
   }
   return true;
}


//带表头结点单链表的撤销
void Destroy(HeaderList* h) {
   Node* p, * q;
   while (h->head->link) {
       q = h->head->link;
       p = h->head->link->link;
       free(h->head->link);
       h->head = q;
   }
}



void main()
{
   int i, x;
   HeaderList list;
   Init(&list);
   for (i = 0; i < 9; i++) {
       Insert(&list, i - 1, i);    //插入0~8
   }
   printf("the linklist is:");
   Output(&list);
   Delete(&list, 0);                //删除0
   printf("\nthe linklist is:");
   Output(&list);
   Find(&list, 0, &x);               //查找下标为0的元素
   printf("\nthe value is:");
   printf("%d ", x);
   Destroy(&list);
}