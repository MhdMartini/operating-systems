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
        enque(currNode);
        currNode = NULL;
    }
    else if (preemtive)
    {
        rQ->enque(currNode);
        currNode = NULL;
    }
    return false;
}
void Scheduler::enque(PNode *pNode)
{
    /* detach input node from ready que and add it to finished que */
    if (fQ == NULL)
    {
        fQ = pNode;
        fQ->next = NULL;
        return;
    }

    PNode *currPNode = fQ;
    PNode *lastPNode = NULL;
    while (currPNode != NULL)
    {
        lastPNode = currPNode;
        currPNode = currPNode->next;
    }
    lastPNode->next = pNode;
    pNode->next = NULL;
}
void Scheduler::display()
{
    while (fQ != NULL)
    {
        fQ->display();
        fQ = fQ->next;
    }
}
