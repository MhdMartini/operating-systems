#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"
#include "ready_que.h"

using namespace std;

Scheduler::Scheduler(FCFS *fcfsQue)
{
    rQ = fcfsQue;
    fQ = (Process **)malloc(rQ->reqQue->nR);
}
bool Scheduler::step(bool preemtive)
{
    /* burst running node and make others wait - return if done */
    rQ->step();
    if (currNode == NULL)
        currNode = rQ->pop();

    if (currNode == NULL)
    {
        if (rQ->reqQue->len == 0)
            return true;
        return false;
    }

    currProcess = currNode->p;
    bool pDone = currProcess->burst();
    rQ->wait();
    if (pDone)
    {
        // add it to finished que
        fQ[currProcess->id] = currProcess;
        currNode = NULL;
    }
    else if (preemtive)
    {
        rQ->enque(currNode);
        currNode = NULL;
    }
    return false;
}
void Scheduler::display()
{
    cout << "FCFS Summary (WT = wait time, TT = turnaround time):" << endl;
    float twAve = 0, ttaAve = 0;
    for (int i = 0; i < rQ->reqQue->nR; i++)
    {
        fQ[i]->display();
        twAve += fQ[i]->tw;
        ttaAve += fQ[i]->tta;
    }
    twAve /= rQ->reqQue->nR;
    ttaAve /= rQ->reqQue->nR;

    cout << "AVG\t" << twAve << "\t" << ttaAve << endl;
}