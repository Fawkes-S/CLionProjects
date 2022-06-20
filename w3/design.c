#include "stdio.h"
#include<malloc.h>
typedef struct {
    int val;
    struct MyLinkedList *next;
} MyLinkedList;


MyLinkedList* myLinkedListCreate() {
    MyLinkedList *head = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    head->next = NULL;
    return head;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    MyLinkedList *cur = obj->next;
    for(int i=0;cur->next!=NULL;i++){
        if(index==i){
            return cur->val;
        }
        else{
            cur=cur->next;
        }
    }
    return -1;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList *rhead = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    rhead->val = val;
    rhead->next = obj->next;
    obj->next = rhead;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList *cur = obj;
    while(cur->next != NULL){
        cur = cur->next;
    }
    MyLinkedList *ntail = (MyLinkedList *)malloc(sizeof (MyLinkedList));
    ntail->val = val;
    ntail->next = NULL;
    cur->next = ntail;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index == 0){
        myLinkedListAddAtHead(obj, val);
        return;
    }
    MyLinkedList *cur = obj->next;
    for (int i = 1 ;cur != NULL; i++){
        if (i == index){
            MyLinkedList* newnode = (MyLinkedList *)malloc(sizeof (MyLinkedList));
            newnode->val = val;
            newnode->next = cur->next;
            cur->next = newnode;
            return;
        }
        else{
            cur = cur->next;
        }
    }
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index == 0){
        MyLinkedList *tmp = obj->next;
        if (tmp != NULL){
            obj->next = tmp->next;
            free(tmp);
        }
        return;
    }
    MyLinkedList *cur = obj->next;
    for (int i = 1 ;cur != NULL && cur->next != NULL; i++){
        if (i == index){
            MyLinkedList *tmp = cur->next;
            if (tmp != NULL) {
                cur->next = tmp->next;
                free(tmp);
            }
            return;
        }
        else{
            cur = cur->next;
        }
    }

}

void myLinkedListFree(MyLinkedList* obj) {
    while(obj != NULL){
        MyLinkedList *tmp = obj;
        obj = obj->next;
        free(tmp);
    }
}

void showLL(MyLinkedList *list) {
    MyLinkedList *p;
    list=list->next;
    for (p = list; p != NULL; p = p->next) {
        if (p->next) {
            printf("%d-->", p->val);
        } else {
            printf("%d", p->val);
        }
    }
    printf("\n");
}
int main(){
    int a,b;
    MyLinkedList *linkedList = myLinkedListCreate();
    myLinkedListAddAtHead(linkedList,1);
    myLinkedListAddAtTail(linkedList,3);
    myLinkedListAddAtIndex(linkedList,1,2); //链表变为1-> 2-> 3
    printf("@@1:\n");
    showLL(linkedList);
    printf("@@2:\n");
    a=myLinkedListGet(linkedList,1);
    printf("%d\n",a);          //返回2
    myLinkedListDeleteAtIndex(linkedList,1);  //现在链表是1-> 3
    printf("@@3:\n");
    showLL(linkedList);
    printf("@@4:\n");
    b=myLinkedListGet(linkedList,1);
    printf("%d",b);          //返回3

}