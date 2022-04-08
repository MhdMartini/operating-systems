#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ready_que.h"
#include "scheduler_ques.h"

class Scheduler
/* run processes in the ready que, amd maintain a process
sequence and number of context switches */
{
private:
    PNode *currNode = NULL; // current running process

public:
    bool pre;
    Process *currProcess;                              // saves the last serviced process
    ReadyQue *rQ;                                      // ready queue
    Process **fQ;                                      // finished queue
    Scheduler(FCFS *fcfsQue, bool preemptive = false); // init with FCFS
    bool step();                                       // run one scheduling cycle
    void display();                                    // display info about finished que
};

#endif