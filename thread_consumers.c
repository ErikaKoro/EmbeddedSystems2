#include "thread_consumers.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    queue *q;
}args;

void *consumer (void *arg){

    args *a = (args *)arg;

    while(1){
        
        workFunction w;
        queueDel(a->q, &w);
        // printf("Consumer: work function received\n");

        if(w.work == NULL){
            // printf("Consumer: work function is NULL\n");
            break;
        }

        w.work(w.userData);

        free(w.userData);

    }
    pthread_exit (NULL);
}

void joinThreads(threadConsumers *cons){

    for(int i = 0; i < cons->thread_num; i++){
        pthread_join(cons->thread_id[i], NULL);
    }

    free(cons->thread_id);
}

void threadsInit(threadConsumers *cons, queue *q, int numOfConsumers){

    args *arg = (args *)malloc(sizeof(args));   
    arg->q = q;
    cons->thread_num = numOfConsumers;
    cons->thread_id = (pthread_t *)malloc(numOfConsumers * sizeof(pthread_t));
    cons->q = q;

    for(int i = 0; i < cons->thread_num; i++){
        pthread_create(&cons->thread_id[i], NULL, consumer, arg);
    }

}