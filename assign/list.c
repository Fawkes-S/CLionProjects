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
    size_t   length;
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

// add a string to the end of the list
void list_push (list L, string str){
    NodeT *new = malloc(sizeof(NodeT));
    if(!new){
        return;
    }
    new->v = (string)malloc(strlen(str)+1);
    strcpy(new->v, str);
    new->next = NULL;
    L->tail->next = new;
    L->tail = new;
    L->length++;
}

// remove the last string of the list
string list_pop (list L){
    if(L->length == 0){
        return NULL;
    }
    // traverse the linked list makes the pointer point to the previous node of the last node of the linked list.
    NodeT* new = L->head;
    while(new->next != L->tail){
        new = new->next;
    }
    // str stored in heap
    string str = (string)malloc( strlen(L->tail->v) + 1);
    strcpy(str, L->tail->v);
    L->tail = new;
    L->tail->next = NULL;
    L->length--;
    return str;
}

// add a string to the start of the list
void list_enqueue (list L, string str){
    NodeT *new = malloc(sizeof(NodeT));
    if(!new){
        return;
    }
    new->v = malloc(strlen(str)+1);
    strcpy(new->v, str);
    new->next = L->head->next;                      // head is null, start from head->next
    L->head->next = new;
    if(L->length == 0){
        L->tail = new;
    }
    L->length++;
}

// remove the last string of the list
string list_dequeue (list L){
    if(L->length == 0){
        return NULL;
    }
    NodeT* new = L->head;
    while(new->next != L->tail){
        new = new->next;
    }
    // str stored in heap
    string str = (string)malloc( strlen(L->tail->v) + 1);
    strcpy(str, L->tail->v);

    L->tail = new;
    L->tail->next = NULL;
    L->length--;
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
    while (new){
        if(strcmp(new->v, str) != 0){                   //new->next->v, str not equals, strcmp(new->v, str) not null
            new = new->next;
        }else{
            return true;
        }
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

