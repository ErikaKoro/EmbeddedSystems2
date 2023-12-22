#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "timer.h"
#include "thread_consumers.h"


#define NUMBER_OF_THREADS 4
#define QUEUE_SIZE 50
#define RUN_TIME 5
#define NUMBER_OF_TIMERS 1
#define PERIOD1 1000
#define PERIOD2 100
#define PERIOD3 10
#define STARTDELAY 0


int main(int argc, char const *argv[]){

    queue q;
    queueInit(&q, QUEUE_SIZE, NUMBER_OF_THREADS);

    Timer t1;
    timerInit(&t1, &q, PERIOD1, (RUN_TIME * 1000) / PERIOD1, STARTDELAY);

    Timer t2;
    timerInit(&t2, &q, PERIOD2, (RUN_TIME * 1000) / PERIOD2, STARTDELAY);

    Timer t3;
    timerInit(&t3, &q, PERIOD3, (RUN_TIME * 1000) / PERIOD3, STARTDELAY);

    threadConsumers cons;
    threadsInit(&cons, &q, NUMBER_OF_THREADS);
    
    t1.timerFnc(&t1);
    t2.timerFnc(&t2);
    t3.timerFnc(&t3);

    start(&t1);
    start(&t2);
    start(&t3);
    // startat(&t, 36, 15, 20, 20, 12, 2023);

    joinThreads(&cons);

    FILE *fp;
    fp = fopen("execution_times/producer.txt", "w");
    for(int i = 0; i < (RUN_TIME * 1000) / PERIOD1; i++){
        fprintf(fp, "%ld\n", t1.producerTimers[i]);
    }
    for(int i = 0; i < (RUN_TIME * 1000) / PERIOD2; i++){
        fprintf(fp, "%ld\n", t2.producerTimers[i]);
    }
    for(int i = 0; i < (RUN_TIME * 1000) / PERIOD3; i++){
        fprintf(fp, "%ld\n", t3.producerTimers[i]);
    }

    fclose(fp);
    
    return 0;
}