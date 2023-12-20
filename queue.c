#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

void queueInit (queue *q, int size, int numOfThreads){

    q->numberOfTimers = 0;
    q->numberOfThreads = numOfThreads;
    q->buf_size = size;
    q->buf = (workFunction *) malloc (size * sizeof (workFunction));
    q->empty = 1;
    q->full = 0;
    q->head = 0;
    q->tail = 0;
    
    pthread_mutex_init (&q->mut, NULL);
    pthread_mutex_init (&q->timerMut, NULL);
    pthread_cond_init (&q->notFull, NULL);
    pthread_cond_init (&q->notEmpty, NULL);

}


void queueDelete (queue *q){

    pthread_mutex_destroy (&q->mut);
    pthread_mutex_destroy (&q->timerMut);
    pthread_cond_destroy (&q->notFull);
    pthread_cond_destroy (&q->notEmpty);
    free (q->buf);
}

/**
 * @brief 
 * 
 * @param q 
 * @param in 
 */
void queueAdd (queue *q, workFunction in){

    pthread_mutex_lock (&q->mut);

    while (q->full) {
        // printf ("producer: queue FULL.\n");
        pthread_cond_wait (&q->notFull, &q->mut);
    }

    struct timeval start;
    gettimeofday(&start, NULL);  // get start time since epoch
    in.timestamp = start.tv_sec * 1000000 + start.tv_usec;
    q->buf[q->tail] = in; 
    q->tail++;
    
    if (q->tail == q->buf_size)
        q->tail = 0;
    if (q->tail == q->head)
        q->full = 1;
    q->empty = 0;

    pthread_mutex_unlock (&q->mut);
    pthread_cond_signal (&q->notEmpty);
}

void queueDel (queue *q, workFunction *out){

    pthread_mutex_lock (&q->mut);

    while (q->empty) {
        // printf ("consumer: queue EMPTY.\n");
        pthread_cond_wait (&q->notEmpty, &q->mut);
    }

    *out = q->buf[q->head];
    q->head++;
    if (q->head == q->buf_size)
        q->head = 0;
    if (q->head == q->tail)
        q->empty = 1;
    q->full = 0;

    pthread_mutex_unlock (&q->mut);
    pthread_cond_signal (&q->notFull);
}

