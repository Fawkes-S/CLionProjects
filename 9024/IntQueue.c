#include "IntQueue.h"
#include <assert.h>

typedef struct {
    int  item[MAXITEMS];
    int  front;
    int  rear;
} queueRep;                   // defines the Data Structure

static queueRep queueObject;  // defines the Data Object

void QueueInit() {
    queueObject.front = 0;
    queueObject.rear = -1;
}

int QueueIsEmpty() {
    if (queueObject.front > queueObject.rear){
        return -1;
    }else{
        return 0;
    }
}

void QueueEnqueue(int da) {
    assert(queueObject.rear < MAXITEMS-1);
    queueObject.rear++;
    int i = queueObject.rear;
    queueObject.item[i] = da;
}

int QueueDequeue() {
    assert(queueObject.front < queueObject.rear+1);
    int i = queueObject.front;
    int da = queueObject.item[i];
    queueObject.front++;
    return da;
}