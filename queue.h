#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct {

    void * (*work)(void *);   // The function to be called
    void * userData;          // The argument to be passed to the function

}workFunction;

typedef struct {
    
    int buf_size;
    workFunction *buf;
    long head, tail;
    int full, empty;
    pthread_mutex_t mut;
    pthread_cond_t notFull, notEmpty;

} queue;

void queueInit (queue *q, int size);

void queueDelete (queue *q);

void queueAdd (queue *q, workFunction in);

void queueDel (queue *q, workFunction *out);

#endif