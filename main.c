#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "timer.h"
#include "thread_consumers.h"


int main(int argc, char const *argv[]){

    int numberOfThreads = 4;
    int queueSize = 10;
    int runTime = 5;

    int numberOfTimers = 1;
    // int *period = (int *)malloc(numberOfTimers * sizeof(int));
    // period[0] = 1000;
    // period[1] = 100;
    int period = 1000;

    int startDelay = 0;
    queue q;
    queueInit(&q, queueSize, numberOfThreads);

    Timer t;
    timerInit(&t, &q, period, (runTime * 1000) / period, startDelay);

    // Timer t2;
    // timerInit(&t2, &q, period[1], (runTime * 1000) / period[1], startDelay);

    threadConsumers cons;
    threadsInit(&cons, &q, numberOfThreads);
    
    // t.timerFnc(&t);
    // t2.timerFnc(&t2);

    // start(&t);
    startat(&t, 1, 1, 1, 1, 1, 1);

    joinThreads(&cons);

    return 0;
}