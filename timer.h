#ifndef TIMER_H
#define TIMER_H

#include "queue.h"

typedef struct{

    queue *queue;  // The queue to be used
    int period;  // The interval between the function calls of TimerFcn >= 1
    int tasksToExecute;  // It gives the number of TimerFnc's executions
    int startDelay;  // The delay before the first TimerFnc call
    
    void * (*startFnc)(void *);  // The function to be called at the start of the timer
    void * (*stopFnc)(void *);  // The function to be called at the end of the TimerFcn executions
    void * (*timerFnc)(void *);  // The function to be called at the beginning of each period
    void * (*errorFnc)(void *); // The function to be called if the queue is full
    void *userData;  // Data to be passed to the queue

    long int *producerTimers;  // The array that holds the time that takes for each timer to add a task in the queue

}Timer;

void timerInit(Timer *t, queue *queue, int period, int tasksToExecute, int startDelay);

void start(Timer *t);

void startat(Timer *t, int secs, int minutes, int hours, int day, int month, int year);

#endif