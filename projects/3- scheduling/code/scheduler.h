#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ready_que.h"
#include "scheduler_ques.h"

class Scheduler
{
public:
    ReadyQue *rQ;
    Scheduler(ReadyQue *readyQue);
    Scheduler(FCFS *fcfsQue);
    void simulate();
};

#endif