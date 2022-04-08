#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "scheduler.h"
#include "ready_que.h"

using namespace std;

Scheduler::Scheduler(ReadyQue *readyQue)
{
    rQ = readyQue;
}
Scheduler::Scheduler(FCFS *fcfsQue)
{
    rQ = fcfsQue;
}
bool Scheduler::step(bool preemtive)
{
    /* simulate a non-preemtive scheduler with any non-preemtive que.
    return if everything is done */

    rQ->step();
    if (currNode == NULL)
        currNode = rQ->pop();

    if (currNode == NULL)
    {
        /* check of ready que is empty because requests are done or
        because requests have not arrived yet */
        if (rQ->reqQue->len == 0)
            return true;
        return false;
    }

    bool pDone = currNode->p->burst();
    rQ->wait();
    if (pDone)
    {
        // add it to finished que
        currNode->display();
        currNode = NULL;
    }
    if (preemtive)
    {
        rQ->enque(currNode);
        currNode = NULL;
    }
    return false;
}