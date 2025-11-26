#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
typedef int Bool;

/*
    二叉搜索树的定义：
    1.任意两个结点的关键字值不同
    2.左子树的所有关键字值小于根节点，右子树的所有关键字值大于根节点
    3.左右子树也是二叉搜索树
*/

//假设二叉树结点中的关键字值就是结点的元素值
//二叉搜索树定义
typedef struct bstNode
{
    int key;    //关键字值
    struct BSTNode *lChild, *rChild     //根结点的左右孩子
}bstNode, *BinarySearchTree;

//二叉搜索树的递归搜索
BinarySearchTree recSearch(BinarySearchTree bst, int k) {

    if (!bst)   //空树返回null
    { 
        return NULL; 
    }

    if (bst->key == k) {        //找到元素返回对应地址
        return bst;
    } 
    else if (k < bst->key) {    //小于元素找左子树
        return recSearch(bst->lChild, k);
    }
    else {      //大于元素找右子树
        return recSearch(bst->rChild, k);
    }
}

//二叉搜索树的迭代搜索
BinarySearchTree iterSearch(BinarySearchTree bst, int k) {
    while (bst)
    {
        if (k < bst->key) {
            bst = bst->lChild;
        } else if (k > bst->key) {
            bst = bst->rChild;
        } else {
            return bst;
        }    
    }
    return NULL;
}

//插入元素
Bool insert(BinarySearchTree bst, int e) {
    bstNode *p = bst, *q, *r;
    while (p)       //对二叉搜索树进行查重
    {
        q = p;
        if (e < p->key) { p = p->lChild; }
        else if(e > p->key) { p = p->rChild; }
        else { return false; }
    }

    r = (bstNode*)malloc(sizeof(bstNode));      //创建新结点
    r->key = e;
    r->lChild = r->rChild = NULL;

    if (!bst) {bst = r;}        //根据二叉搜索树的定义插入节点
    else if (e < q->key) {q->lChild = r;}
    else {q->rChild = r;}
    
    return true;
}

//删除节点
//需要让删除节点之后的树也是二叉搜索树
Bool delete(BinarySearchTree bst, int k) {
    bstNode *c, *r, *s, *p = bst, *q;

    while (p&& p->key != k)     //从根节点查找关键字为k的结点p
    {
        q = p;      //q是p的双亲节点
        if (k < p->key) {p = p->lChild;}
        else {p = p->rChild;}
    }
    
    if (!p) {return false;}     //找不到结点就返回false

    if (p->lChild && p->rChild)     //p有两棵非空子树
    {
        s = p->rChild;
        r = p;

        while (s->lChild)       //搜索p的中序后继结点s
        {
            r = s;
            s = s->lChild;
        }
        
        p->key = s->key;    //令p指向被删除的结点，q指向p的双亲
        p = s;
        q = r;
    }
    
    if (p->lChild) {c = p->lChild;}     //令c指向取代p的那可子树
    else {c = p->rChild;}
    
    if (p == bst) {bst = c;}        //如果删除的是根节点，则结点c成为根
    else if (p == q->lChild) {q->lChild = c;}   //否则c取代p
    else {q->rChild = c;}

    free(p);
    return true;
}