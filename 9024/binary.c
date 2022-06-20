#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

int main(){
    StackInit();
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    while(n>0){
        StackPush(n%2);
        n /=2;
    }
    while(!StackIsEmpty()){
        printf("%d",StackPop());
    }
}