#ifndef SCHEDULER_QUES_H
#define SCHEDULER_QUES_H
#include "ready_que.h"

class FCFS : public ReadyQue
{
    using ReadyQue::ReadyQue;

public:
    void enque(PNode *pNode);
};

#endif