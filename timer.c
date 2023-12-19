#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


/**
 * @brief    :This function is executed when the timer object is created.
 * @param arg:
*/
void *startFnc(void *arg){
    printf("Oh hi Timer!\n");
}

/**
 * @brief    :This function is executed after the last call of TimerFnc.
 * @param arg:
*/
void *stopFnc(void *arg){
    printf("Oh Bye Timer!\n");
}

/**
 * @brief  :The function to be called at the beginning of each period.
 * @param t:The timer object
*/
void *errorFnc(void *arg){
    printf("Oh no! The queue is full!\n");
}


// ------------- TIMERFNC IMPLEMENTATION -------------- //

/**
 * @brief This struct contains the user Data(args) for the work function
 */
typedef struct{
  int a;
  int b;
  int sum;
}userArgs;


/**
 * @brief This function implements the task that must be executed by the consumers
 * 
 * @param arg 
 * @return void* 
 */
void *work(void *arg){

  userArgs *a = (userArgs *)arg;
  a->sum = a->a + a->b;
  printf("\tThe sum is: %d\n", a->sum);
  return (NULL);
}


/**\
 * @brief    :The function to be called at the beginning of each period. It adds a task to the queue.
 * @param arg:A pointer to the timer object 
 */
void *producer (void *arg){

    Timer *t = (Timer *)arg;

    // The queue where tasks are added by the producer thread
    queue *fifo = t->queue;

    for (int i = 0; i < t->tasksToExecute; i++) {

        // The queue is being filled by workfunction structs
        workFunction in;
        in.work = work;
        userArgs *args = (userArgs *)malloc(sizeof(userArgs));
        args->a = 1;
        args->b = 2;
        args->sum = 0;
        in.userData = args;

        printf("Adding task %d to queue...\n", i + 1);
        queueAdd(fifo, in);

        // The producer thread adds a task per period
        usleep (t->period * 1000);

    }


    if(fifo->numberOfTimers == 1){

        workFunction termination;
        termination.work = NULL;
        termination.userData = NULL;
        for(int i = 0; i < fifo->numberOfThreads; i++){
        queueAdd(fifo, termination);
        }

    }
    else{
        
        pthread_mutex_lock(&fifo->timerMut);
        fifo->numberOfTimers--;
        pthread_mutex_unlock(&fifo->timerMut);

    }
    pthread_exit(NULL);

}


/**
 * @brief The function to be called at the beginning of each period.
 * 
 * @param arg : Timer object
 * @return void* 
 */
void *timerFnc(void *arg){

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t id;
    pthread_create(&id, &attr, producer, arg);  
    pthread_join(id, NULL);
}

/**
 * @brief  :Initializes the timer.
 * @param t:The timer object
 * @param queue: The queue to be used by the timer
 * @param period: The period between the function calls of TimerFnc
 * @param tasksToExecute: the number of TimerFnc's executions
 * @param startDelay: The delay before the first TimerFnc call
*/
void timerInit(Timer *t, queue *queue, int period, int tasksToExecute, int startDelay){

    t->queue = queue;
    t->queue->numberOfTimers++;
    t->period = period;
    t->tasksToExecute = tasksToExecute;
    t->startDelay = startDelay;

    t->startFnc = startFnc;
    t->stopFnc = stopFnc;
    t->timerFnc = timerFnc;
    t->errorFnc = errorFnc;

    // t->userData = userData;

}

/**
 * @brief Starts the timer and the first execution of TimerFnc.
 * 
 * @param t : Object of type Timer
 */
void start(Timer *t){

    t->startFnc(NULL);
    t->timerFnc(t);

}


/**
 * @brief       Starts the timer at the given time.
 * 
 * @param t :   Object of type Timer
 * @param secs : Seconds
 * @param minutes : Minutes
 * @param hours : Hours
 * @param day : Day
 * @param month : Month
 * @param year : Year
 */
void startat(Timer *t, int secs, int minutes, int hours, int day, int month, int year){

    // start the timer at the given time day/month/year hours:minutes:secs
    t->startFnc(NULL);

    // convert the given time to a struct timeval
    struct tm specificTime = {0};
    time_t t_of_day;

    specificTime.tm_sec = secs;
    specificTime.tm_min = minutes;
    specificTime.tm_hour = hours;
    specificTime.tm_mday = day;
    specificTime.tm_mon = month - 1;
    specificTime.tm_year = year - 1900;

    t_of_day = mktime(&specificTime);

    // get the current time
    struct timeval now;
    gettimeofday(&now, NULL);

    // calculate the difference between the given time and the current time
    int diff = (int)(t_of_day - now.tv_sec);
    printf("The difference is: %d\n", diff);

    // if the difference is negative, the given time has already passed
    if(diff < 0){
        printf("The given time has already passed!\n");
        t->startDelay = 0;
        return;
    }
    else{
        t->startDelay = diff;
    }

    t->timerFnc(t);    

}