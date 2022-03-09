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

/* structure to hold input arguments to threads callback functions */
struct ThreadArgs
{
    int nVals; // number of values to be stored
    int id;    // thread id
};

/* helper functions */
void initMonitor(int buffLen);
void store(int val, int prodId);
void *produce(void *args);
void load(int consId);
void *consume(void *args);
void cleanUp(void);

#endif