#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "scheduler.h"
#include "ready_que.h"

using namespace std;

Scheduler::Scheduler(FCFS *fcfsQue) { rQ = fcfsQue; }
bool Scheduler::step(bool preemtive)
{
    /* burst running node and make others wait - return if done */

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
