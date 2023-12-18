#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "timer.h"


int main(int argc, char const *argv[]){

    pthread_mutex_t mut;
    pthread_cond_t notFull, notEmpty;

    queue q;
    queueInit(&q, 10);

    Timer t;
    timerInit(&t, &q, 1000, 10, 0);
    
    t.timerFnc(&t);

    return 0;
}