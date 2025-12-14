#include "Quene.h"
#define true 1
#define false 0

typedef int boolean;
typedef char elemType;

//二叉树结点结构体
typedef struct Node
{
    struct Node *LChild, *RChild;   //结点的左右孩子
    elemType element;              //数据体
} Node;

//二叉树结构体
typedef struct BinaryTree
{
    Node *root;                     //根节点
} BinaryTree;

//创建空树
void initTree(BinaryTree *tree) {
    tree->root = NULL;
}

//创建结点
Node* createNode(elemType x, Node *lc, Node *rc) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->element = x;
    p->LChild = lc;
    p->RChild = rc;
    return p;
}

//返回根节点的值
boolean getRoot(BinaryTree *tree, elemType *x) {
    if (tree->root)
    {
        x = tree->root->element;
        return true;
    }
    else
        return false;
}

//创建二叉树
void makeTree(BinaryTree *tree, elemType e, BinaryTree *left, BinaryTree *right) {

    if (tree->root || left == right)    //如果根节点非空或者左右节点相同则不能创建树
        return;

    tree->root = createNode(e, left->root, right->root);
    left->root = right->root = NULL;
}

/*
    二叉树先序遍历算法（VLR）的步骤：
    1. 访问根节点
    2. 先序遍历左子树
    3. 先序遍历右子树
*/
void VLR(Node *node) {
    if (!node) return;  //跳过空节点
    printf("%c", node->element);    //访问节点
    VLR(node->LChild);  //先序遍历左子树
    VLR(node->RChild);  //先序遍历右子树
}
void VLR_Tree(BinaryTree *tree) {
    VLR(tree->root);
}

/*
    中序遍历（LVR）步骤：
    1. 中序遍历左子树
    2. 访问根节点
    3. 中序遍历右子树
*/
void LVR(Node *node){
    if (!node) return;
    LVR(node->LChild);
    printf("%c", node->element);
    LVR(node->RChild);
}
void LVR_Tree(BinaryTree *tree) {
    LVR(tree->root);
}

/*
    后序遍历（LRV）步骤：
    1. 后序遍历左子树
    2. 后序遍历右子树
    3. 访问根节点
*/
void LRV(Node *node) {
    if (!node) return;
    LRV(node->LChild);
    LRV(node->RChild);
    printf("%c", node->element);
}
void LRV_Tree(BinaryTree *tree) {
    LRV(tree->root);
}

/*
    层次遍历步骤（假设是一棵非空二叉树）：
    1. 创建队列q，将根节点入队
    2. 判断q是否是空队列，是空队列退出遍历
    3. 获取队头结点p，然后将p出队
    4. 如果p存在左孩子，则将左孩子进队
    5. 如果p存在右孩子，则将右孩子进队
*/
void LevelOrder(BinaryTree *tree) {
    if (!tree->root) return;

    queue q;
    create(&q, 100);
    Node *p = tree->root;
    enQueue(&q, p);
    while (!isEmpty(&q))
    {
        getFront(&q, &p);
        deQueue(&q);
        printf("%c", p->element);
        if (p->LChild) enQueue(&q, p->LChild);
        if (p->RChild) enQueue(&q, p->RChild);
    }
    destroy(&q);
}


//主函数
int main() {
    BinaryTree a, b, x, y, z;
    initTree(&a);
    initTree(&b);
    initTree(&x);
    initTree(&y);
    initTree(&z);
    makeTree(&y, 'E', &a, &b);
    makeTree(&z, 'F', &a, &b);
    makeTree(&x, 'C', &a, &b);
    makeTree(&y, 'D', &a, &b);
    makeTree(&z, 'B', &a, &b);
    VLR(&z);
}