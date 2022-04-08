#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ready_que.h"
#include "scheduler_ques.h"

class Scheduler
{
private:
    PNode *currNode = NULL;

public:
    ReadyQue *rQ;
    Scheduler(ReadyQue *readyQue);
    Scheduler(FCFS *fcfsQue);
    void simulate();
    bool step(bool preemtive = false);
};

#endif