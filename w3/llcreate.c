#include "stdio.h"
#include<malloc.h>
#include "assert.h"
#include "string.h"
#include "stdlib.h"

typedef struct node {
    int data;
    struct node *next;
} NodeT;
NodeT *makeNode(int v) {
    NodeT *L  = (NodeT*)malloc(sizeof(NodeT));
    assert(L != NULL);
    L->data = v;
    L->next = NULL;
    return L;
}
int isEmpty(NodeT *list){
    if(list->next){
        return 0;
    }else{
        return 1;
    }
}
void freeLL(NodeT *list) {
    NodeT *p, *temp;
    p = list;
    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
    }
}
void freeRight(NodeT *list) {
    NodeT *p;
    if(list){
        p=list->next;
        free(list);
        freeRight(p);
    }
}
void freeWrong(NodeT *list) {
    if(list->next){
        freeWrong(list->next);
    }
    if(list){
        free(list);
    }
}
void freeWrong2(NodeT *list) {
    NodeT *p;
    if(list){
        p=list->next;
        free(list);
        if(p){
            freeWrong2(p->next);
        }
    }
}
void showLL(NodeT *list) {
    NodeT *p;
    list=list->next;
    for (p = list; p != NULL; p = p->next) {
        if (p->next) {
            printf("%d-->", p->data);
        } else {
            printf("%d", p->data);
        }
    }
}
NodeT *joinLL(NodeT *list, int v) {
    NodeT *p,*q;
    p=list;
    q=list->next;
    while(q){
        p=q;
        q=q->next;
    }
    NodeT *L = makeNode(v);
    L->next = p->next;
    p->next=L;
    return list;
}
int isDigit(char *ch){
    int i=0;
    if(ch[0]=='-'){
        i++;
    }
    for(;i< strlen(ch);i++){
        if(ch[i]>'9'||ch[i]<'0')
            return 0;
    }
    return 1;
}
int main(){
    char ch[BUFSIZ];
    int t=0;
    NodeT *all;
    all = makeNode(0); //Initialised
    while(1){
        printf("Enter an integer: ");
        scanf("%s", ch);
        if(isDigit(ch)){
            int v = atoi(ch);
            all = joinLL(all, v);
            t++;
        }else{
            break;
        }
    }
    if(t==0)
        printf("Done.");
        else{
            printf("Done. List is ");
            showLL(all);
        }
//    freeWrong(all);
//    if(isEmpty(all)){
//        printf("empty");
//    }else{
//        printf("Not");
//    }
    return 0;
}