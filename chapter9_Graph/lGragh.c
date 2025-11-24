#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

typedef int elemtype;

//边结点定义
//表示两个顶点之间的边
typedef struct eNode
{
    int adjVex;                 //与任意顶点u邻接的顶点
    elemtype weight;            //边的权重值
    struct eNode* nextArc;      //下一边节点的地址
}eNode;

//邻接表定义
typedef struct lGragh
{
    int n;          //图的顶点数
    int e;          //图的边数

    //指向一维指针数组，数组的下标表示顶点的编号，数组的元素是与对应顶点邻接的顶点集合
    eNode **a;      
}lGragh;

typedef int status;

//邻接表初始化
status init(lGragh *lg, int nSize) {
    int i;

    lg->n = nSize;      //初始化顶点数量和边数量
    lg->e = 0;
    lg->a = (eNode**)malloc(nSize * sizeof(eNode*));    //生成长度为n的一维指针数组

    if (!lg->a) { return false; }   //生成失败返回false
    else {
        for (i = 0; i < lg->n; i++) {lg->a[i] = NULL;}  //将指针数组a设置为空
        return true;
    }
}

//邻接表撤销
void destroy(lGragh *lg) {
    eNode *p, *q;

    for (int i = 0; i < lg->n; i++)
    {
        p = lg->a[i];   //指针p指向顶点i的单链表（就是与顶点i邻接的顶点集合）的第一个边结点
        q = p;          //q是待删除结点

        while (p)       //依次释放顶点i单链表中的所有边结点
        {
            p = p->nextArc;     //指向下一个结点
            free(q);            //释放上一个结点的内存
            q = p;              //指向下一个待删除结点
        }
    }
    
    free(lg->a);        //删除所有链表之后删除一位指针数组
}

//搜索边
status exist(lGragh *lg, int u, int v) {
    eNode *p;

    if (u < 0 || v < 0 || u > lg->n-1 || v > lg->n-1 || u == v) {return false;}

    p = lg->a[u];       //指针p指向顶点u的单链表的第一个边结点

    while (p&& p->adjVex != v) {p = p->nextArc;}    //遍历邻接顶点链表，直到找到顶点v

    if (!p) {return false;}     //遍历完成后，如果p不存在说明不存在对应的边
    else {return true;}
}

//插入边
status insertEdge(lGragh *lg, int u, int v, elemtype weight) {
    eNode *p;

    if (u < 0 || v < 0 || u > lg->n-1 || v > lg->n-1 || u == v ||
        exist(lg, u, v)) {
        return false;
    }

    p = (eNode*)malloc(sizeof(eNode));      //为边结点分配空间
    p->adjVex = v;      //邻接的顶点
    p->weight = weight;     //权重

    p->nextArc = lg->a[u];      //将边结点插到邻接顶点链表的最前面
    lg->a[u] = p;
    lg->e++;

    return true;
}

//删除边
status removeEdge(lGragh *lg, int u, int v) {
    eNode *p, *q;

    if (u < 0 || v < 0 || u > lg->n-1 || v > lg->n-1 || u == v) {return false;}

    p = lg->a[u];
    q = NULL;

    while (p&& p->adjVex != v)      //遍历邻接顶点链表，直到找到待删除顶点
    {
        q = p;      //p和q有先后次序，q总是p的前驱结点
        p = p->nextArc;
    }
    
    if (!p) {return false;}     //遍历完成后，若p不存在表示待删除边不存在
    
    if (q) {q->nextArc = p->nextArc;}    //删除顶点链表中的顶点，即删除边
    else {lg->a[u] = p->nextArc;}

    free(p);
    lg->e--;

    return true;
}

//输出邻接表
void displayLGraph(lGragh *lg) {
    eNode *p;

    for (int i = 0; i < lg->n; i++)
    {
        printf("%d -> ", i);      //输出所有顶点

        p = lg->a[i];       //p指向顶点链表的表头
        while (p)
        {
            printf("%d ", p->adjVex);
            p = p->nextArc;
        }
        
        printf("\n");
    }
    
}

//主函数
int main() {
    int n = 6;
    lGragh lg;
    init(&lg, n);       //生成含有6个顶点的邻接表
    
    insertEdge(&lg, 0, 1, 1);       //插入亿点边
    insertEdge(&lg, 0, 2, 1);
    insertEdge(&lg, 1, 2, 1);
    insertEdge(&lg, 1, 3, 1);
    insertEdge(&lg, 1, 5, 1);
    insertEdge(&lg, 2, 3, 1);
    insertEdge(&lg, 2, 4, 1);
    insertEdge(&lg, 2, 1, 1);
    insertEdge(&lg, 3, 2, 1);
    insertEdge(&lg, 3, 1, 1);
    insertEdge(&lg, 3, 4, 1);
    insertEdge(&lg, 4, 5, 1);
    insertEdge(&lg, 4, 2, 1);
    insertEdge(&lg, 5, 1, 1);
    insertEdge(&lg, 5, 2, 1);



    displayLGraph(&lg);     //输出邻接表

    int u = 3, v = 5;
    status flag = exist(&lg, u, v);     //搜索边
    if (flag)
    {
        printf("边(%d, %d)存在", u, v);
    } else {
        printf("边(%d, %d)不存在", u, v);
    } 

    destroy(&lg);

    return 0;
}