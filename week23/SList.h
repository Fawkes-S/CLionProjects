#ifndef __SLIST_H__
#define __SLIST_H__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

//单链表结点
typedef struct Node
{
    ElemType data;      //数据域
    struct Node *next;  //指针域
}Node, *PNode;

//单链表管理结构
typedef struct List
{
    PNode  first; //指向头结点
    PNode  last;  //指向尾结点
    size_t size;  //记录有效结点数
}List;

void InitList(List *list);

void push_back(List *list, ElemType x);
void push_front(List *list, ElemType x);
void show_list(List *list);

void pop_back(List *list);
void pop_front(List *list);
void insert_val(List *list, ElemType x);
Node* find(List *list, ElemType key);
int  length(List *list);
void delete_val(List *list, ElemType key);
void sort(List *list);
void resver(List *list);
void clear(List *list);
void destroy(List *list);
void split(List *list,List *left);

//代码优化/
typedef Node* It;
Node* _buynode(ElemType x);
It begin(List *list);
It end(List *list);
void insert(List *list, It pos, ElemType x);
#endif //__SLIST_H__
