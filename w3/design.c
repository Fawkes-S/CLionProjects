#include "stdio.h"
#include<malloc.h>
typedef struct MyLinked_List{
    int val;
    struct MyLinkedList *next;
} MyLinkedList;


MyLinkedList* myLinkedListCreate() {
    MyLinkedList *head = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    head->next = NULL;
    return head;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if(index<0||obj->next==NULL){
        return -1;
    }
    MyLinkedList *cur = obj->next;
    for(int i=0;i<index;i++){
        if(!cur->next){
            return -1;
        }else
            cur=cur->next;
    }
    return cur->val;
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
    if(index<=0){
        myLinkedListAddAtHead(obj, val);
        return;
    }
    MyLinkedList *cur=obj->next;
    for(int i=0;i<index-1;i++){
        if(!cur->next){
            myLinkedListAddAtTail(obj, val);
            return;
        }
        else{
            cur=cur->next;
        }
    }
    MyLinkedList *p = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    p->val = val;
    p->next=cur->next;
    cur->next = p;
    return;
}
void myLinkedListAddAtIndex_1(MyLinkedList* obj, int index, int val) {
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

void myLinkedListDeleteAtIndex_1(MyLinkedList* obj, int index) {
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

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList *cur=obj->next;
    if(cur->next==NULL){
        obj->next=NULL;
        return;
    }
    if(index==0&&cur->next){
        obj->next = cur->next;
        return;
    }
    for(int i=1;i<index;i++){
        if(cur->next==NULL){
            return;
        }else{
            cur=cur->next;
        }
    }
    if(cur->next==NULL){
        return;
    }else{
        MyLinkedList *temp = cur->next;
        cur->next=temp->next;
    }
    return;
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
MyLinkedList* reverseList(MyLinkedList* head){
    MyLinkedList *pre = NULL;
    MyLinkedList *cur = head->next;
    MyLinkedList *next;
    while(cur){
        next = cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    return pre;
}
int main(){
    int a,b,c;
    MyLinkedList *linkedList = myLinkedListCreate();
    MyLinkedList *rList = myLinkedListCreate();
    //showLL(linkedList);
    myLinkedListAddAtHead(linkedList,1);
//    myLinkedListDeleteAtIndex(linkedList,0);
//    showLL(linkedList);
    myLinkedListAddAtTail(linkedList,3);
    myLinkedListAddAtIndex(linkedList,1,2); //链表变为1-> 2-> 3
    printf("@@1:\n");
    showLL(linkedList);
    rList=reverseList(linkedList);
    printf("Show after reversing:\n");
    showLL(rList);

//    printf("@@2:\n");
//    a=myLinkedListGet(linkedList,1);
//    printf("%d\n",a);          //返回2
//    myLinkedListDeleteAtIndex(linkedList,1);  //现在链表是1-> 3
//    printf("@@delete index 3:\n");
//    myLinkedListDeleteAtIndex(linkedList,3);
//    showLL(linkedList);
//    printf("@@delete index 0 -1:\n");
//    myLinkedListDeleteAtIndex(linkedList,0);
//    showLL(linkedList);
//    printf("@@delete index 0 -2:\n");
//    myLinkedListDeleteAtIndex(linkedList,0);
//    showLL(linkedList);

}
//int main(){
//    int a,b,c;
//    MyLinkedList *linkedList = myLinkedListCreate();
//    myLinkedListAddAtHead(linkedList,4);
//    myLinkedListAddAtHead(linkedList,1);
//    myLinkedListAddAtHead(linkedList,5);
//    myLinkedListDeleteAtIndex(linkedList,3);
//    showLL(linkedList);
//    myLinkedListAddAtHead(linkedList,7);
//    myLinkedListAddAtHead(linkedList,1);
//    showLL(linkedList);
//    myLinkedListDeleteAtIndex(linkedList,4);
//
//
//}