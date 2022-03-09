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

void store(int val, int prodId)
/* store val in the shared monitor structure*/
{
    // while buffer is full, release lock and wait to be awaken
    bool slept = false;
    while (buffFull)
    {
        slept = true;
        printf("P%d: Blocked due to full buffer\n", prodId);
        pthread_cond_wait(&monitor.cvFull, &monitor.lock);
    }
    if (slept)
        printf("P%d Done waiting on full buffer\n", prodId);

    // print what you'll do
    printf("P%d: Writing %d to position %d\n", prodId, val, monitor.end);

    // store value at write index, and store the write index in
    // the input pointer
    monitor.buffer[monitor.end] = val;

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
/* store n values in the shared monitor structure
input is a structure containing the producer ID and
the number of values to be produced */
{
    int nVals = ((struct ThreadArgs *)args)->nVals;
    int prodId = ((struct ThreadArgs *)args)->id;

    printf("P%d: Producing %d values\n", prodId, nVals);

    for (int i = 0; i < nVals; i++)
    {
        int val = rand() % 11;
        pthread_mutex_lock(&monitor.lock); // acquire the lock
        store(val, prodId);
        pthread_mutex_unlock(&monitor.lock); // release lock
    }
    printf("P%d: Exiting\n", prodId);
    return 0;
}

void load(int consId)
/* load val from the shared monitor structure and store
the write index and value consumed in the input pointers */
{
    // while buffer is empty, release lock and wait to be awaken
    bool slept = false;
    while (buffEmpty)
    {
        slept = true;
        printf("C%d Blocked due to empty buffer\n", consId);
        pthread_cond_wait(&monitor.cvEmpty, &monitor.lock);
    }
    if (slept)
        printf("C%d Done waiting on empty buffer\n", consId);

    // print what you'll do and load
    int val = monitor.buffer[monitor.start];
    printf("C%d: Reading %d from position %d\n", consId, val, monitor.start);

    // increment read index (circular fashion)
    monitor.start = (monitor.start + 1) % monitor.len;

    // decide if buffer is empty
    buffEmpty = (monitor.end == monitor.start);

    // set buffer full as false and signal for a producer waiting bc buffer was full
    buffFull = false;
    pthread_cond_signal(&monitor.cvFull);
}

void *consume(void *args)
/* load n values from the shared monitor structure
input is a structure containing the consumer ID and
the number of values to be consumed */
{
    int nVals = ((struct ThreadArgs *)args)->nVals;
    int consId = ((struct ThreadArgs *)args)->id;

    int readIdx, val;
    printf("C%d: Consuming %d values\n", consId, nVals);

    for (int i = 0; i < nVals; i++)
    {
        pthread_mutex_lock(&monitor.lock); // acquire the lock
        load(consId);
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