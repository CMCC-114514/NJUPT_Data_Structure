#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1

typedef int elemtype;

//图的邻接矩阵mGraph定义
typedef struct mGraph
{
    elemtype **a;       //邻接矩阵
    int n;              //图的当前顶点数
    int e;              //图的当前边数
    elemtype noEdge;    //两顶点之间没有边时的值
}mGraph;

typedef int status;

//邻接矩阵初始化
status init(mGraph *mg, int nSize, elemtype noEdgeValue) {
    int i,j;

    mg->n = nSize;      //初始化顶点数量
    mg->e = 0;          //初始图没有边
    mg->noEdge = noEdgeValue;   //初始化没有边时的取值（没有加权时为0）
    mg->a = (elemtype**)malloc(nSize * sizeof(elemtype*));  //生成长度为n的一维指针数组

    if (!mg->a) {return false;}   //生成数组失败时返回false

    for (i = 0; i < mg->n; i++)
    {
        mg->a[i] = (elemtype*)malloc(nSize * sizeof(elemtype));     //生成长度为n的一维数组

        for (j = 0; j < mg->n; j++)
        {
            mg->a[i][j] = mg->noEdge;   //如此来生成二位数组表示邻接矩阵
        }

        mg->a[i][i] = 0;    //图中没有环，所以对角线上的值均为0
        
    }

    return true;
}

//邻接矩阵撤销
void destroy(mGraph *mg) {
    for (int i = 0; i < mg->n; i++)
    {
        free(mg->a[i]);     //释放n个一维数组的空间
    }
    free(mg->a);     //释放一维指针数组的空间
}

//搜索边
status exist(mGraph *mg, int u, int v) {
    if (u < 0 ||
        v < 0 ||
        u > mg->n-1 ||
        v > mg->n-1 ||
        u == v ||   //u和v无效的情况：超出范围或者相等

        mg->a[u][v] == mg->noEdge   //矩阵中元素值等于无边时的值，表示这两个点之间没有边存在
    )
    {
        return false;
    }
    return true;
}

//插入边
//如果边没有权重，则weight=1，否则weight等于权重值
status insertEdge(mGraph *mg, int u, int v, elemtype weight) {
    if (u < 0 || v < 0 || u > mg->n-1 || v > mg->n-1 || u == v || mg->a[u][v] != mg->noEdge) 
    {
        return false;   //插入的边已存在或u和v无效，返回false
    }
        
    mg->a[u][v] = weight;   //插入新的边
    mg->e++;
    return true;
}

//删除边
status removeEdge(mGraph *mg, int u, int v) {
    if (u < 0 || v < 0 || u > mg->n-1 || v > mg->n-1 || u == v || mg->a[u][v] == mg->noEdge)
    {
        return false;   //插入的边不存在或u和v无效，返回false
    }

    mg->a[u][v] = mg->noEdge;   //删除选中的边
    mg->e--;
    return true;
}

//输出邻接矩阵
void displayMGraph(mGraph *mg) {
    for (int i = 0; i < mg->n; i++)
    {
        for (int j = 0; j < mg->n; j++)
        {
            printf("%d\t", mg->a[i][j]);
        }
        printf("\n");
    }
}

//main函数
int main() {
    int n = 6;
    mGraph mg;
    init(&mg, n, 0);    //生成含有6个顶点的图及对应的邻接矩阵

    for (int i = 0; i < n; i++)     //按一定条件插入边
    {
        if (n % 3 == 0)
        {
            insertEdge(&mg, i, i+1, 1);
            insertEdge(&mg, i, i+2, 1);
        }
    }
    
    displayMGraph(&mg);     //输出矩阵

    int u = 3, v = 5;
    status flag = exist(&mg, u, v);     //搜索边
    if (flag)
    {
        printf("边(%d, %d)存在", u, v);
    } else {
        printf("边(%d, %d)不存在", u, v);
    } 

    destroy(&mg);       //删除邻接矩阵
    
    return 0;
}