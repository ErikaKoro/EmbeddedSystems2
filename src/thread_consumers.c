#include "thread_consumers.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/**
 * @brief args for each thread
 * 
 */
typedef struct{
    queue *q;
    int thread_id;
}args;

void *consumer (void *arg){

    args *a = (args *)arg;

    FILE *fp;
    // open file with name: "thread_id.txt"
    char filename[100];
    sprintf(filename, "execution_times/consumer_%d.txt", a->thread_id);
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error opening file! %s\n", filename);
        exit(1);
    }

    while(1){
        
        workFunction w;
        queueDel(a->q, &w);

        struct timeval time_deq;
        gettimeofday(&time_deq, NULL);  // get time in which a task was dequeued
        // calculate the time that the task was in the queue
        long int time_in_queue = time_deq.tv_sec * 1000000 + time_deq.tv_usec - w.timestamp;
        fprintf(fp, "%ld\n", time_in_queue);

        // printf("Consumer: work function received\n");

        if(w.work == NULL){
            // printf("Consumer: work function is NULL\n");
            break;
        }

        w.work(w.userData);

        free(w.userData);

    }
    fclose(fp);
    pthread_exit (NULL);
}

void joinThreads(threadConsumers *cons){

    for(int i = 0; i < cons->thread_num; i++){
        pthread_join(cons->thread_id[i], NULL);
    }

    free(cons->thread_id);
}

void threadsInit(threadConsumers *cons, queue *q, int numOfConsumers){

    args *arg = (args *)malloc(sizeof(args) * numOfConsumers);   
    
    cons->thread_num = numOfConsumers;
    cons->thread_id = (pthread_t *)malloc(numOfConsumers * sizeof(pthread_t));
    cons->q = q;

    for(int i = 0; i < cons->thread_num; i++){
        arg[i].thread_id = i;
        arg[i].q = q;
        pthread_create(&cons->thread_id[i], NULL, consumer, arg + i);
    }

}