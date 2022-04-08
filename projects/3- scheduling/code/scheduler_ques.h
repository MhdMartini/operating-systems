#ifndef SCHEDULER_QUES_H
#define SCHEDULER_QUES_H
#include "ready_que.h"
#include <string>

class FCFS : public ReadyQue
{
    using ReadyQue::ReadyQue;
    void enque(PNode *pNode);
};

#endif