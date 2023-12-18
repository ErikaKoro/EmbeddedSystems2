#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


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

    printf("Adding task to queue...\n");
    queueAdd(fifo, in);

    // The producer thread adds a task per period
    usleep (t->period * 1000);

  }

  while (fifo->empty == 0)
  {
    workFunction out;
    printf("Removing task from queue...\n");
    queueDel(fifo, &out);

    out.work(out.userData);

    free(out.userData);
  }
  
  pthread_exit(NULL);

}


/**
 * @brief The function to be called at the beginning of each period.
 * 
 * @param arg 
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
    t->period = period;
    t->tasksToExecute = tasksToExecute;
    t->startDelay = startDelay;

    t->startFnc = startFnc;
    t->stopFnc = stopFnc;
    t->timerFnc = timerFnc;
    t->errorFnc = errorFnc;

    // t->userData = userData;

}


void *consumer (void *q){

  queue *fifo;
  int i, d;

  fifo = (queue *)q;

  for (i = 0; i < LOOP; i++) {
    queueDel (fifo, &d);
    usleep (50000);
  }
  return (NULL);
}