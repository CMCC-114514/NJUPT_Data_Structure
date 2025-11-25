#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define neverUsed -99

typedef int Bool;

//散列表结构体定义
typedef struct hashtable
{
    int length;         //散列表长度
    int num;            //当前散列表中的元素数量
    Bool *empty;        //empty标记数组
    int *elements;      //元素数组
}hashTable;

//散列表初始化
void create(hashTable *hashTable, int size) {

    hashTable->length = size;       //设置散列表长度
    hashTable->num = 0;             //初始化时元素数量为0
    hashTable->empty = (Bool*)malloc(sizeof(Bool) * size);      //初始化标记数组和元素数组
    hashTable->elements = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        hashTable->empty[i] = true;     //标记为空
        hashTable->elements[i] = neverUsed;   //散列表没有被使用
    }
}

//散列表销毁
void destroy(hashTable *hashTable) {
    free(hashTable->empty);
    free(hashTable->elements);
}

//散列表清空
void clear(hashTable *hashTable) {

    hashTable->num = 0;

    for (int i = 0; i < hashTable->length; i++)
    {
        hashTable->elements[i] = true;
        hashTable->elements[i] = neverUsed;
    }
}

//散列表判空
Bool isEmpty(hashTable *hashTable) {
    if (hashTable->num == 0) {return true;}
    else {return false;}
}

//散列表判满
Bool isFull(hashTable *hashTable) {
    if (hashTable->num == hashTable->length) {return true;}
    else {return false;}
}

//散列函数（除留余数法）
int hash(int length, int key) {
    return key % length;
}

//查找元素
int search(hashTable *hashTable, int key) {
    int anchor, pos;

    anchor = pos = hash(hashTable->length, key);    //计算基地址

    do {
        if (hashTable->empty[pos]) {return false;}      //对应的位置为空返回false
        if (hashTable->elements[pos] == key) {return pos;}  //找到元素返回位置
        pos = (pos + 1) % hashTable->length;    //设置下一个搜索位置
    } while (pos != anchor);

    return false;   //找完整个散列表都没找到，返回false
}

//插入元素
Bool insertElement(hashTable *ht, int key) {
    int anchor, i;

    if (isFull(ht))         //如果散列表已满，返回false
    {
        return false;
    }

    if (search(ht, key) != false)       //如果待插入元素已存在，返回false
    {
        return false;
    }
    
    anchor = i = hash(ht->length, key);     //计算基地址

    do
    {
        if (ht->elements[i] == neverUsed)       //若当前位置未被占用，将新元素存入当前位置
        {
            ht->elements[i] = key;
            ht->empty[i] = false;
            ht->num++;
            return true;
        }
        i = (i + 1) % ht->length;       //使用线性探查法考察下一个位置
    } while (i != anchor);
    
    return false;
}

//删除元素
Bool deleteElement(hashTable *ht, int key) {

    if (isEmpty(ht))            //若散列表为空，返回false
    {
        return false;
    }

    int pos = search(ht, key);      //查找元素

    if (pos == false)       //若元素不存在，返回false
    {
        return false;
    } 
    else {                  //存在就删除元素并返回true
        ht->elements[pos] = neverUsed;
        ht->num--;
        return true;  
    }
}

//输出散列表
void output(hashTable *ht) {
    for (int i = 0; i < ht->length; i++)
    {
        printf("%5d", ht->elements[i]);
    }
    printf("\n");
    for (int i = 0; i < ht->length; i++)
    {
        printf("%5d", ht->empty[i]);
    }
    printf("\n");
}

//主函数
int main() {
    hashTable ht;

    create(&ht, 9);     //创建长度为9的散列表

    for (int i = 15; i < 15 + ht.length; i++)   //插入9个数据
    {
        insertElement(&ht, i);
    }

    output(&ht);    //输出散列表
    destroy(&ht);
}