#ifndef THREAD_CONSUMERS_H_
#define THREAD_CONSUMERS_H_

#include "queue.h"
#include <pthread.h>


typedef struct{
    pthread_t *thread_id;
    int thread_num;
    queue *q;
}threadConsumers;


void threadsInit(threadConsumers *cons, queue *q, int numOfConsumers);
void joinThreads(threadConsumers *cons);

#endif 


