#include <stdio.h>
#include "IntQueue.h"

int main(){
    QueueInit();

    for(int i =0; i<4;i++){
        QueueEnqueue(i);

    }
    while(!QueueIsEmpty()){
        printf("%d",QueueDequeue());
    }
}