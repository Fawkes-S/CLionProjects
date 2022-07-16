#include "list.h"

int main(){
    list list = list_create();
    //尾 push pop
    //list_push(list, (string) "s"); // s
    list_pop(list); //
    show(list);
    list_enqueue(list, (string)"h"); //h
    list_dequeue(list); //gst
    show(list);
}