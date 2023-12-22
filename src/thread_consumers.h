#ifndef THREAD_CONSUMERS_H_
#define THREAD_CONSUMERS_H_

#include "queue.h"
#include <pthread.h>


/**
 * @brief struct for the thread pool
 * 
 */
typedef struct{
    pthread_t *thread_id;  // the array of thread ids
    int thread_num;  // the number of threads
    queue *q;  // the queue to be used by the threads
    
}threadConsumers;


void threadsInit(threadConsumers *cons, queue *q, int numOfConsumers);
void joinThreads(threadConsumers *cons);

#endif 


