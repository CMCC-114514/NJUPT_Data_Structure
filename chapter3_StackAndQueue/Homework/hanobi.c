/*
* 要求 *
汉诺塔问题：
1.有三个柱，分别为起始柱，辅助柱，目标柱，起始柱上有n（n>=1)个盘子，从下到上逐渐变小
2.问题的目标是将起始柱的所有盘子通过辅助柱移动到目标柱上
3.移动时，每次只能移动一个盘子，而且大盘子不能放在小盘子上
给出汉诺塔问题的递归算法和非递归算法
*/

//////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

//递归算法
/*
* 算法思想 *
用数字大小代表盘子的大小
先分成两种情况：
1.如果这个塔只含有一个盘子，则直接将盘子移动到目标盘
2.如果这个塔含有n个盘子，那么将问题从“将最大的盘子n通过辅助柱移动到目标柱”
  转化为“将次大的盘子n-1通过辅助柱移动到目标柱”
然后对于情况二，算法步骤为：
1. 将n-1个盘子从起始柱移动到辅助柱
2. 将最大的盘子从起始柱移动到目标柱
3. 将n-1个盘子从辅助柱移动到目标柱
*/

void hanoi1(int n, char from, char to, char dest) {
    // 情况1：如果只有一个盘子，直接移动
    if (n == 1) {
        printf("盘子 1 从 %c 移动到 %c\n", from, to);
        return;
    }

    // 情况2的递归步骤：
    // 1. 将n-1个盘子从起始柱移动到辅助柱
    hanoi1(n - 1, from, dest, to);

    // 2. 将最大的盘子从起始柱移动到目标柱
    printf("盘子 %d 从 %c 移动到 %c\n", n, from, to);

    // 3. 将n-1个盘子从辅助柱移动到目标柱
    hanoi1(n - 1, dest, to, from);
}

//非递归算法
/*
* 算法思想 *
汉诺塔问题的非递归算法需要借助堆栈来实现
用三个堆栈代表三个柱子，然后根据盘子数量的奇偶性来决定盘子第一步的移动方向
偶数个盘子：起始柱->辅助柱, 起始柱->目标柱, 辅助柱->目标柱
奇数个盘子：起始柱->目标柱, 起始柱->辅助柱, 目标柱->辅助柱
*/
//定义堆栈
typedef int elemtype;
typedef struct stack{
    elemtype* element;
    int top;
    int maxsize;
} Stack;

//堆栈初始化
Stack* createStack(int maxsize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->element = (int*)malloc(sizeof(int) * maxsize);
    stack->top = -1;
    stack->maxsize = maxsize;
    return stack;
}

// 移动盘子的辅助函数
void moveDisk(Stack* stacks[], int fromIdx, int toIdx, char fromChar, char toChar, char auxChar) {
    char poleNames[3] = { fromChar, auxChar, toChar };

    // 检查从fromIdx移动到toIdx是否合法
    if (stacks[fromIdx]->top >= 0 &&
        (stacks[toIdx]->top < 0 ||
            stacks[fromIdx]->element[stacks[fromIdx]->top] < stacks[toIdx]->element[stacks[toIdx]->top])) {

        int disk = stacks[fromIdx]->element[stacks[fromIdx]->top--];
        stacks[toIdx]->element[++stacks[toIdx]->top] = disk;
        printf("将盘子 %d 从 %c 移动到 %c\n", disk, poleNames[fromIdx], poleNames[toIdx]);
    }
    // 检查从toIdx移动到fromIdx是否合法
    else if (stacks[toIdx]->top >= 0 &&
        (stacks[fromIdx]->top < 0 ||
            stacks[toIdx]->element[stacks[toIdx]->top] < stacks[fromIdx]->element[stacks[fromIdx]->top])) {

        int disk = stacks[toIdx]->element[stacks[toIdx]->top--];
        stacks[fromIdx]->element[++stacks[fromIdx]->top] = disk;
        printf("将盘子 %d 从 %c 移动到 %c\n", disk, poleNames[toIdx], poleNames[fromIdx]);
    }
}

void hanoi2(int n, char from, char to, char aux) {
    if (n <= 0) return;

    // 使用三个堆栈来表示三个柱子
    Stack* stacks[3];
    stacks[0] = createStack(n);  // 起始柱A
    stacks[1] = createStack(n);  // 辅助柱B  
    stacks[2] = createStack(n);  // 目标柱C

    // 初始化起始柱，最大的盘子在底部
    for (int i = n; i >= 1; i--) {
        stacks[0]->element[++stacks[0]->top] = i;
    }

    // 总移动次数
    int totalMoves = (1 << n) - 1;  // 2^n - 1

    // 根据盘子数量的奇偶性决定第一步的移动方向
    char src = 0, dest, temp;

    if (n % 2 == 0) {
        // 偶数个盘子：A->B, A->C, B->C
        dest = 1;
        temp = 2;
    }
    else {
        // 奇数个盘子：A->C, A->B, C->B
        dest = 2;
        temp = 1;
    }

    for (int move = 1; move <= totalMoves; move++) {
        if (move % 3 == 1) {
            // 在src和dest之间移动
            moveDisk(stacks, src, dest, from, to, aux);
        }
        else if (move % 3 == 2) {
            // 在src和temp之间移动
            moveDisk(stacks, src, temp, from, to, aux);
        }
        else {
            // 在dest和temp之间移动
            moveDisk(stacks, dest, temp, from, to, aux);
        }
    }
}

int main() {
    int n;

    printf("请输入汉诺塔的盘子数量：");
    scanf_s("%d", &n);

    printf("汉诺塔的移动步骤：\n");
    hanoi1(n, 'A', 'C', 'B');  // 递归算法：A是起始柱，C是目标柱，B是辅助柱
    //hanoi2(n, 'A', 'C', 'B');   // 非递归算法：A是起始柱，C是目标柱，B是辅助柱

    return 0;
}