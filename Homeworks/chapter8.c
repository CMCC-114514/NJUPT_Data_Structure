#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define none 0

typedef int status;

//定义学生结构体
typedef struct student
{
    int id;
    char name;
    char grade;
}student;

//学生信息输入
void setInfo(student *s, int id, char name, char grade) {
    s->id = id;
    s->name = name;
    s->grade = grade;
}

//学生信息输出
void outputInfo(student s) {
    if (s.id != none) {printf("%d\t%c\t%c\n", s.id, s.name, s.grade);}
}

//定义学生散列表
typedef struct studentHT
{
    int length;     //给出哈希表的长度等参数
    int num;
    status *empty;

    student *students;
}studentHT;

//散列表初始化
status create(studentHT *ht, int length) {
    student emptyS;
    setInfo(&emptyS, none, none, none);     //设置空学生对象

    ht->length = length;    //设置散列表长度
    ht->num = 0;    //散列表元素个数为0

    ht->empty = (status*)malloc(sizeof(status) * length);   //生成对应数组
    ht->students = (student*)malloc(sizeof(student) * length);

    if (!ht->empty || !ht->students)
    {
        return false;   //创建失败则返回false
    }
    

    for (int i = 0; i < ht->length; i++)
    {
        ht->empty[i] = true;        //将散列表中的元素设置为空
        ht->students[i] = emptyS;
    }
    
    return true;
}

//散列表销毁
void destroy(studentHT *ht) {
    free(ht->empty);
    free(ht->students);
}

//散列表判空
status isEmpty(studentHT *ht) {
    if (ht->num == 0) {return true;}
    else {return false;}
}

//散列表判满
status isFull(studentHT *ht) {
    if (ht->num == ht->length) {return true;}
    else {return false;}
}

//散列函数
//观察到学生们的学号的首位没有重复，所以直接取学号首位作为基地址
int hash(int key) {
    return key / 10;
}

//搜索元素
status search(studentHT *ht, int key) {
    int anchor, pos;

    anchor = pos = hash(key);    //计算基地址

    do {
        if (ht->empty[pos]) {return false;}      //对应的位置为空返回false
        if (ht->students[pos].id == key) {return pos;}  //找到元素返回位置
        pos = (pos + 1) % ht->length;    //设置下一个搜索位置
    } while (pos != anchor);

    return false;   //找完整个散列表都没找到，返回false
}

//插入元素
status insertStudent(studentHT *ht, student s) {
    int anchor, i;

    if (isFull(ht))         //如果散列表已满，返回false
    {
        return false;
    }

    if (search(ht, s.id) != false)       //如果待插入元素已存在，返回false
    {
        return false;
    }
    
    anchor = i = hash(s.id);     //计算基地址

    do
    {
        if (ht->students[i].id == 0)       //若当前位置未被占用，将新元素存入当前位置
        {
            ht->students[i] = s;
            ht->empty[i] = false;
            ht->num++;
            return true;
        }
        i = (i + 1) % ht->length;       //使用线性探查法考察下一个位置
    } while (i != anchor);
    
    return false;
}

//输出散列表
void output(studentHT *ht) {
    printf("学号\t姓名\t成绩\n");
    for (int i = 0; i < ht->length; i++)
    {
        outputInfo(ht->students[i]);
    }
    printf("\n");
    // for (int i = 0; i < ht->length; i++)
    // {
    //     printf("%5d", ht->empty[i]);
    // }
    // printf("\n");
}

//主函数
int main() {
    //使用ABCD代表成绩的优良中差

    student s1;     //创建学生对象
    setInfo(&s1, 70, 'A', 'A');

    student s2;
    setInfo(&s2, 25, 'B', 'B');    

    student s3;
    setInfo(&s3, 80, 'C', 'C');    
    
    student s4;
    setInfo(&s4, 35, 'D', 'D');    
    
    student s5;
    setInfo(&s5, 60, 'E', 'C');

    studentHT ht;       //创建散列表
    create(&ht, 7);

    insertStudent(&ht, s1);     //插入学生对象
    insertStudent(&ht, s2);
    insertStudent(&ht, s3);
    insertStudent(&ht, s4);
    insertStudent(&ht, s5);

    output(&ht);        //输出散列表

    status flag = search(&ht, 60);
    if (flag)
    {
        printf("学号60的学生在散列表中");
    }
    
    destroy(&ht);

    return 0;
}