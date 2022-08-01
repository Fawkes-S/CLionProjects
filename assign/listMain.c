#include <stdio.h>
#include "list.h"
#include "string.h"
#include <stdlib.h>
#include "string.h"

int main(){
    list list = list_create();
    //尾 push pop
    list_push(list, (string) "http://www.cse.unsw.edu.au/~cs9024/micro-web/index.html"); // s
    list_push(list, (string) "http://www.cse.unsw.edu.au/~cs9024/micro-web/X.html"); // s
    printf("1.^^%d\n", list_is_empty(list));
    list_push(list, (string) "http://www.cse.unsw.edu.au/~cs9024/micro-web/Y.html"); // s
    size_t size1 = list_length(list);
    printf("@@ %d\n", size1);
    list_remove(list, (string) "http://www.cse.unsw.edu.au/~cs9024/micro-web/dsa.html");
    show(list);
//    //list_pop(list);
//    list_enqueue(list, (string)"s"); //h
//    printf("contain: %d\n", list_contains(list,"sad"));
//    //list_enqueue(list, (string)"h"); //h
////    string a;
////    a = list_dequeue(list);
////    printf("%s\n", a);
//    //list_add(list, (string)"http://www.cse.unsw.edu.au/~cs9024/micro-web/index.html");
//    show(list);
//    //bool b = list_contains(list, (string)"http://www.cse.unsw.edu.au/~cs9024/micro-web/index.html");
//    //string d = list_pop(list);
//    string d = list_dequeue(list);
//    printf("2.^^%d\n", list_is_empty(list));
//    printf("%%%%%\n");
//    printf("pop: %s\n", d);
//    //printf("%s\n", d);
//    string aa = "ad";
//    size_t size = strlen(aa);
//    printf("size@@: %zu\n",size);
//    list_dequeue(list);
//    show(list);
//    list_dequeue(list);
//    show(list);
//    printf("3.^^%d\n", list_is_empty(list));

}
