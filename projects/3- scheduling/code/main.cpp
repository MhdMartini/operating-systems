/*
Process
    - holds process-related information
    - process helpful functions:
        * burst
        * wait

PNode
    - process node class to hold a process and point to a next process
    - used by requests que to sort requests by arrival time

Requests
    - reads and stores all requests from file
    - sorts the requests according to arrival time as a linked list
    - step method:
        updates the end and len attributes:
            * end tells us how many requests to read at a give time
            * len tells us how many requests remain.

ReadyQue

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "process.h"
#include "requests.h"
#include "ready_que.h"
#include "scheduler_ques.h"
#include "scheduler.h"
#include "scheduler_stats.h"

using namespace std;

int main(int argc, char *argv[])
{
    char *fileIn = argv[1];
    char *fileOut = argv[2];
    int interval = atoi(argv[3]);

    Requests reqQue(fileIn);
    FCFS fcfs(&reqQue, "FCFS");
    Scheduler sch(&fcfs);

    simulate(&sch, fileOut, interval);
    return 0;
}