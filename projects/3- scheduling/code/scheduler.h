#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ready_que.h"
#include "scheduler_ques.h"

class Scheduler
{
private:
    PNode *currNode = NULL;

public:
    ReadyQue *rQ;             // ready queue
    PNode *fQ = NULL;         // finished queue
    Scheduler(FCFS *fcfsQue); // init with FCFS
    bool step(bool preemtive = false);
};

#endif