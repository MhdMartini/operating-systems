#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "prod_cons_MT.h"

MONITOR monitor; // global variable - buffer data structure
bool buffFull = false;
bool buffEmpty = true;

int main(int argc, char *argv[])
{
    // make sure all input arguments are there
    assert(argc == 4);

    // store input arguments
    int buffLen = atoi(argv[1]); // buffer length
    int nProd = atoi(argv[2]);   // number of producers
    int nCons = atoi(argv[3]);   // number of consumers

    // validate input arguments
    assert(buffLen > 0);
    assert(nProd > 0);
    assert(nCons > 0);

    initMonitor(buffLen);

    // number of stores per producer
    int nStoresProd = buffLen * 2;

    // total number of stores
    int nStoresTotal = nStoresProd * nProd;

    // number of loads per consumer
    int nLoadsCons = nStoresTotal / nCons;

    // number of loads for last consumer
    int nLoadsConsLast = nLoadsCons + (nStoresTotal % nCons);

    // create producer and comsumer threads arrays
    pthread_t producers[nProd];
    pthread_t consumers[nCons];

    // start producers
    for (int i = 0; i < nProd; i++)
    {
        struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
        args->nVals = nStoresProd;
        args->id = i;
        // printf("\n%d, %d\n", nStoresProd, args->nVals);
        // printf("\n%d, %d\n", i, args->id);

        pthread_create(&producers[i], NULL, produce, (void *)args);
        printf("Main: started producer %d\n", i);
    }

    // start consumers
    for (int i = 0; i < nCons; i++)
    {
        // decide number of consumer values
        int nVals = nLoadsCons;
        if (i == nCons - 1)
            nVals = nLoadsConsLast;

        struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
        args->nVals = nVals;
        args->id = i;
        pthread_create(&consumers[i], NULL, consume, (void *)args);
        printf("Main: started consumer %d\n", i);
    }

    // join producers
    for (int i = 0; i < nProd; i++)
    {
        pthread_join(producers[i], NULL);
        printf("producer %d joined\n", i);
    }

    // join consumers
    for (int i = 0; i < nCons; i++)
    {
        pthread_join(consumers[i], NULL);
        printf("consumer %d joined\n", i);
    }

    printf("Main: program complete\n");

    // Clean up and exit
    cleanUp();
    return 0;
}