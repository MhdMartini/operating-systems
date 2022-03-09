#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include "prod_cons_MT.h"

extern MONITOR monitor;
extern bool buffFull, buffEmpty;

void initMonitor(int buffLen)
/* initialize monitor object */
{
    // initialize buffer
    monitor.len = buffLen;
    monitor.start = 0;
    monitor.end = 0;
    monitor.buffer = (int *)malloc(buffLen * sizeof(int));

    // initialize synch primitives
    pthread_mutex_init(&monitor.lock, NULL);
    pthread_cond_init(&monitor.cvFull, NULL);
    pthread_cond_init(&monitor.cvEmpty, NULL);
}

void store(int *writeIdx, int val)
/* store val in the shared monitor structure*/
{
    // store value at write index, and store the write index in
    // the input pointer
    monitor.buffer[monitor.end] = val;
    *writeIdx = monitor.end;

    // set buffer empty as false
    buffEmpty = false;

    // increment write index (circular fashion)
    monitor.end = (monitor.end + 1) % monitor.len;

    // decide if buffer is full
    buffFull = (monitor.end == monitor.start);

    // signal for a consumer waiting bc buffer was empty
    pthread_cond_signal(&monitor.cvEmpty);
}

void *produce(void *args)
/* store n_vals values in the shared monitor structure and
print which producer store val and where -
help from:
stackoverflow.com/questions/13131982/create-thread-passing-arguments*/
{
    int nVals = ((struct ThreadArgs *)args)->nVals;
    int prodId = ((struct ThreadArgs *)args)->id;

    // printf("\n%d, %d\n", nVals, prodId);

    int writeIdx;
    printf("P%d: Producing %d values\n", prodId, nVals);

    for (int i = 0; i < nVals; i++)
    {
        int val = rand() % 11;
        bool slept = false;

        pthread_mutex_lock(&monitor.lock); // acquire the lock

        // while buffer is full, release lock and wait to be awaken
        while (buffFull)
        {
            printf("P%d: Blocked due to full buffer\n", prodId);
            slept = true;
            pthread_cond_wait(&monitor.cvFull, &monitor.lock);
        }
        if (slept)
            printf("P%d Done waiting on full buffer\n", prodId);

        store(&writeIdx, val);
        printf("P%d: Writing %d to position %d\n", prodId, val, writeIdx);
        pthread_mutex_unlock(&monitor.lock); // release lock
    }
    printf("P%d: Exiting\n", prodId);
    return 0;
}

void load(int *readIdx, int *readVal)
/* load val from the shared monitor structure and store
the write index and value consumed in the input pointers */
{
    // load value at read index
    *readIdx = monitor.start;
    int val = monitor.buffer[monitor.start];
    *readVal = val;

    // increment read index (circular fashion)
    monitor.start = (monitor.start + 1) % monitor.len;

    // decide if buffer is empty
    buffEmpty = (monitor.end == monitor.start);

    // set buffer full as false and signal for a producer waiting bc buffer was full
    buffFull = false;
    pthread_cond_signal(&monitor.cvFull);
}

void *consume(void *args)
/* load n values from the shared monitor structure and
print which consumer loaded the value and from where */
{
    int nVals = ((struct ThreadArgs *)args)->nVals;
    int consId = ((struct ThreadArgs *)args)->id;

    int readIdx, val;
    printf("C%d: Consuming %d values\n", consId, nVals);

    for (int i = 0; i < nVals; i++)
    {
        pthread_mutex_lock(&monitor.lock); // acquire the lock
        // while buffer is empty, release lock and wait to be awaken

        bool slept = false;
        while (buffEmpty)
        {
            printf("C%d Blocked due to empty buffer\n", consId);
            slept = true;
            pthread_cond_wait(&monitor.cvEmpty, &monitor.lock);
        }
        if (slept)
            printf("C%d Done waiting on empty buffe\n", consId);

        load(&readIdx, &val);
        printf("C%d: Reading %d from position %d\n", consId, val, readIdx);
        pthread_mutex_unlock(&monitor.lock); // release lock
    }
    printf("C%d: Exiting\n", consId);
    return 0;
}

void cleanUp(void)
{
    pthread_mutex_destroy(&monitor.lock);
    pthread_cond_destroy(&monitor.cvFull);
    pthread_cond_destroy(&monitor.cvEmpty);
    pthread_exit(NULL);
}