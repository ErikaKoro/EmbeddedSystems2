#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"


int main(int argc, char const *argv[])
{
    queue q;
    queueInit(&q, 10);
    
    return 0;
}