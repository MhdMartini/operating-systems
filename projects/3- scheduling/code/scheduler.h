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
    ReadyQue *rQ;                      // ready queue
    PNode *fQ = NULL;                  // finished queue
    Scheduler(FCFS *fcfsQue);          // init with FCFS
    bool step(bool preemtive = false); // run one scheduling cycle
    void enque(PNode *pNode);          // add a process node to the finished que
    void display();                    // display info about finished que
};

#endif