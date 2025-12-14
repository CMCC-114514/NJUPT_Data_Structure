#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define maxsize 100     //稀疏矩阵可以存储的非零元素上限

typedef int elemType;
typedef int boolean;

//三元组结构体定义
typedef struct Term
{
    int col, row;           //稀疏矩阵中的列下标col和行下标row
    elemType value;         //非零元素值
} Term;

//稀疏矩阵的三元组表结构体定义
typedef struct SparseMatrix
{
    int row, col, num;      //矩阵的行数row，列数col和非零元素个数num
    Term table[maxsize];    //三元组表主体
} SparseMatrix;

/*
    稀疏矩阵的第一个转置算法
    步骤一：依次访问稀疏矩阵A的行三元组表中的每一个元素，交换行列号之后保存在另一个三元组表B中
    步骤二：将B中的元素按照行号i从小到大排序
*/

//冒泡排序算法
// SparseMatrix bubbleSort(SparseMatrix* A){
//     int i, j;
//     for (i = 0; i < A->num; i++)
//     {
//         //boolean isSwap = false;
//         for (j = 0; j < i; j++)
//         {
//             if (A->table[j].row > A->table[j + 1].row)
//             {
//                 Term temp;
//                 temp = A->table[j];
//                 A->table[j] = A->table[j+1];
//                 A->table[j+1] = temp;
//                 //isSwap = true;
//             }
//         }
//     }
// 	return *A;
// }

//转置算法1
// SparseMatrix transpose1(SparseMatrix *A, SparseMatrix *B){

//     //步骤一
//     for (int i = 0; i < A->num; i++)
//     {
//         B->table[i].row = A->table[i].col;
//         B->table[i].col = A->table[i].row;
//         B->table[i].value = A->table[i].value;        
//     }
    
//     //步骤二
//     return bubbleSort(B);
// }

/*
	稀疏矩阵的快速转置算法：
	步骤一：对A的行三元组表进行第一次扫描，找到下标j = 0的所有三元组
*/

int main() {
    SparseMatrix s;
    SparseMatrix b;

    s.row = 6;			//设置行数和列数，非零元素个数为7
	s.col = 6;
	s.num = 7;

	int m[6][6] = { 0 };	//定义稀疏矩阵m并赋值
	m[0][0] = -5;
	m[0][1] = -2;
	m[1][3] = -6;
	m[3][1] = -3;
	m[4][0] = -7;
	m[4][3] = -4;
	m[5][2] = -1;

	int k = 0;
	for (int i = 0; i < 6; i++)		//将稀疏矩阵存储到三元组表中
	{
		for (int j = 0; j < 6; j++)
		{
			if (m[i][j] != 0)
			{
				s.table[k].row = i;
				s.table[k].col = j;
				s.table[k].value = m[i][j];
				k++;
			}
		}
	}
	
	//输出转置前的三元组表
	printf("转置前：\n");
	for (int i = 0; i < s.num; i++)
	{
		printf("%d %d %d\n", s.table[i].row, s.table[i].col, s.table[i].value);
	}

	b = transpose1(&s, &b);
	printf("\n转置后：\n");
	for (int i = 0; i < b.num; i++)
	{
		printf("%d %d %d\n", b.table[i].row, b.table[i].col, b.table[i].value);
	}
}