#include "timer.h"


/**
 * @brief  :Initializes the timer.
 * @param t:The timer object
 * @param queue: The queue to be used by the timer
 * @param period: The period between the function calls of TimerFnc
 * @param tasksToExecute: the number of TimerFnc's executions
 * @param startDelay: The delay before the first TimerFnc call
 * @param startFnc: The function to be called when the timer starts
 * @param stopFnc: The function to be called at the end of the TimerFcn executions
 * @param timerFnc: The function to be called at the beginning of each period
 * @param errorFnc: The function to be called if the queue is full
 * @param userData: Data to be passed to the queue
*/
void timerInit(Timer *t, queue *queue, int period, int tasksToExecute, int startDelay, void *startFnc, void *stopFnc, void *timerFnc, void *errorFnc, void *userData){

    t->queue = queue;
    t->period = period;
    t->tasksToExecute = tasksToExecute;
    t->startDelay = startDelay;

    t->startFnc = startFnc;
    t->stopFnc = stopFnc;
    t->timerFnc = timerFnc;
    t->errorFnc = errorFnc;

    t->userData = userData;

}

/**
 * @brief  :Starts the timer.
 * @param t:The timer object
*/
void *startFnc(void *arg){
    printf("Oh hi Timer!\n");
}

/**
 * @brief  :Stops the timer.
 * @param t:The timer object
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


void *timerFnc(void *arg){

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t id;
    pthread_create(&id, &attr, producer, arg);
}

typedef struct{
  int a;
  int b;
  int sum;
}userArgs;

void *work(void *arg){

  userArgs *a = (userArgs *)arg;
  a->sum = a->a + a->b;
  return (NULL);
}

/**\
 * @brief    :The function to be called at the beginning of each period. It adds a task to the queue.
 * @param arg:A pointer to the timer object 
 */
void *producer (void *arg){

  Timer *t = (Timer *)arg;

  queue *fifo = t->queue;

  for (int i = 0; i < t->tasksToExecute; i++) {

    workFunction in;
    in.work = work;
    userArgs *args = (userArgs *)malloc(sizeof(userArgs));
    args->a = 1;
    args->b = 2;
    args->sum = 0;
    in.userData = args;

    queueAdd(fifo, in);

    // The producer thread adds a task per period
    usleep (t->period * 1000);

  }

  pthread_exit(NULL);

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