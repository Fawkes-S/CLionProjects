#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

// Node of linked list
typedef struct Node{
    string v;                    // value
    struct Node *next;           // pointer
}NodeT;

typedef struct List_Repr{
    int   length;
    NodeT *head;
    NodeT *tail;
}List_Repr;

list list_create (){
    list L = malloc(sizeof(List_Repr));
    L->head = L->tail = calloc(1,sizeof(NodeT));
    if(!L->head){
        return NULL;
    }
    L->head->next = NULL;
    L->length = 0;
    return L;
}

void list_destroy (list L){
    if(L->length == 0){
        return;
    }
    NodeT *p = L->head->next;
    while(p){
        L->head->next = p->next;
        free(p);
        p = L->head->next;
    }
    L->tail = L->head;
    L->length = 0;
    //free(L->head);
    free(L);
}

bool list_is_empty (list L){
    return (L->length == 0);
}

size_t list_length (list L){
    if(!L){
        return 0;
    }else
    {
        return L->length;
    }
}
//尾插
void list_push (list L, string str){
    NodeT *new = malloc(sizeof(NodeT));
    new->v = malloc(strlen(str)+1);
    if(!new){
        return;
    }
    strcpy(new->v, str);
    //new->v = str;
    new->next = NULL;
    L->tail->next = new;
    L->tail = new;

    L->length++;
}
//尾删 ??
string list_pop (list L){
    if(L->length == 0){
        return NULL;
    }

    NodeT* new = L->head; // 定义一个结构体指针指向头结点
    while(new->next != L->tail){ // 遍历链表使node指针指向链表最后一个结点的前一个结点
        new = new->next;
    }
    // str stored in heap
    string str = (string)malloc( strlen(new->v) + 1);
    strcpy(str, L->tail->v);
    //str = L->tail->v;

    //free(L->tail); // 释放node指针所指向的结点的下一个结点，也就是链表的最后一个结点
    L->tail = new;
    L->tail->next = NULL;
    L->length--;
    return str;
}
//头插
void list_enqueue (list L, string str){
    NodeT *new = malloc(sizeof(NodeT));
    if(!new){
        return;
    }
    new->v = malloc(strlen(str)+1);
    strcpy(new->v, str);
//    new->v = str;
    new->next = L->head->next;       // head is null, start from head->next
    L->head->next = new;
    if(L->length == 0){
        L->tail = new;
    }
    L->length++;
}
//头删
string list_dequeue (list L){
    if(L->length == 0){
        return NULL;
    }
    NodeT *new = L->head->next;
    L->head->next = new->next;
    if (L->length == 0) {
        L->tail = L->head;
    }
    L->length--;
    string str = (string)malloc( strlen(new->v) + 1);
    strcpy(str, new->v);

    //free(new);
    return str;
}

void list_add (list L, string str){
    if(list_contains(L, str)){
        return;
    }else{
        list_push(L, str);
    }
}

void list_remove (list L, string str){
    if(L->length == 0){
        return;
    }
    NodeT *new = L->head;
    while (new->next && strcmp(new->next->v, str)){      // when equally, strcmp() is 0
        new = new->next;
    }
    if(!new->next){
        return;
    }
    if(new->next == L->tail){
        list_pop(L);
    }else{
        NodeT *p = new->next;
        new->next = p->next;
        free(p);
        L->length--;
    }
}

bool list_contains (list L, string str){
    NodeT *new = L->head->next;
    //    printf("########\n");
    //    show(L);
    //    printf("########\n");
    while (new){
        if(strcmp(new->v, str) != 0){    //new->next->v, str not equals, strcmp(new->v, str) not null
            new = new->next;
        }else{
            return true;
        }
//        if(new->v != str){
//            new = new->next;
//        }else{
//            return true;
//        }
    }
    return false;
}

void show(list L){
    NodeT *p = L->head->next;
    while (p){
        printf("%s-->",p->v);
        p=p->next;
    }
    printf("END.\n");
}

