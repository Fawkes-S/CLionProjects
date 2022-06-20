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
void freeLL(NodeT *list) {
    NodeT *p, *temp;
    p = list;
    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
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
    printf("\n");
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
    for(int i=0;i< strlen(ch);i++){
        if(ch[i]>'9'||ch[i]<'0')
            return 0;
    }
    return 1;
}
NodeT *split(NodeT *list, NodeT *right){
    NodeT *slow,*fast;
    slow = list->next;
    fast = list->next->next;
    while(fast!=NULL &&fast->next != NULL){
        slow =slow->next;
        fast = fast->next->next;
    }
    right->next = slow->next;
    slow->next = NULL;
    return right;
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
        NodeT *right = makeNode(0);
        right = split(all,right);
        printf("First part is ");
        showLL(all);
        if(right->next){
            printf("Second part is ");
            showLL(right);
            freeLL(right);
        }
    }
    freeLL(all);


    return 0;
}