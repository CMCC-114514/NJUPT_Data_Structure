/*
设计一种高效的转置算法，将稀疏矩阵进行转置
*/

///////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
typedef int elemtype;
#define maxsize 100

#define C 6		//矩阵的行数R和列数C
#define R 6

//三元组定义
typedef struct Term
{
	int col, row;		//行坐标row和列坐标col
	elemtype value;		//元素值
}term;

//三元组表定义
typedef struct SparseMatrix
{
	int m, n, t;		//原矩阵的行数m和列数n，t为非零元素个数
	term table[maxsize];	//三元组表主体
}sparsematrix;

//稀疏矩阵的快速转置算法
sparsematrix transpose(sparsematrix a)
{
	int num[C] = { 0 };		//定义辅助数组num和k，长度均为稀疏矩阵a的列数
	int sum[C] = { 0 };
	
	for (int i = 0; i < a.t; i++)
	{
		//数组num存储矩阵每一列的非零元素个数
		//通过三元组表a统计原矩阵每一列的非零元素个数
		//数组的下标i就代表原矩阵的第i列，对应的元素num[i]就代表非零元素个数
		num[a.table[i].col]++;		
	}

	for (int i = 1; i < C; i++)
	{
		//数组sum存储矩阵a中列号从0到i-1的所有非零元素的个数
		//比如sum[3]就存储了列号从0到2的所有非零元素的个数
		//sum[i]的值决定了原矩阵中第i列的第一个非零元素在三元组表中的位置
		//比如sum[2]=4，说明第2列第一个非零元素在三元组表中的下标是4
		sum[i] = sum[i - 1] + num[i - 1];
	}

	sparsematrix b;
	b.m = C;
	b.n = R;
	b.t = 7;

	for (int i = 0; i < a.t; i++)
	{
		int index = sum[a.table[i].col]++;
		b.table[index].col = a.table[i].row;
		b.table[index].row = a.table[i].col;
		b.table[index].value = a.table[i].value;
	}

	return b;
}

int main()
{
	sparsematrix s;		//定义三元组表s

	s.m = R;			//设置行数和列数，非零元素个数为7
	s.n = C;
	s.t = 7;

	int m[R][C] = { 0 };	//定义稀疏矩阵m并赋值
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
	for (int i = 0; i < s.t; i++)
	{
		printf("%d %d %d\n", s.table[i].row, s.table[i].col, s.table[i].value);
	}

	s = transpose(s);
	printf("\n转置后：\n");
	for (int i = 0; i < s.t; i++)
	{
		printf("%d %d %d\n", s.table[i].row, s.table[i].col, s.table[i].value);
	}
}