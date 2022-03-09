#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

/* monitor structure, stores buffer, buffer related variables and
buffer access primitives */
typedef struct
{
    int start; // write index
    int end;   // read index
    int len;   // length of buffer
    int *buffer;

    pthread_mutex_t lock;
    pthread_cond_t cvFull;  // for threads waiting bc buffer is full
    pthread_cond_t cvEmpty; // for threads waiting bc buffer is empty
} MONITOR;

/* structure to hold the input arguments of the producer threads */
typedef struct
{
    int nVals; // number of values to be stored
    int id;    // thread id
} ThreadArgs;

/* helper functions */
void initMonitor(int buffLen);
void store(int *writeIdx, int val);
void *produce(void *args);
void load(int *readIdx, int *readVal);
void *consume(void *args);
void cleanUp(void);

#endif