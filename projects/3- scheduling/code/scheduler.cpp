#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"
#include "ready_que.h"

using namespace std;

Scheduler::Scheduler(FCFS *fcfsQue, bool preemptive)
{
    rQ = fcfsQue;
    fQ = (Process **)malloc(rQ->reqQue->nR);
    pre = preemptive;
}
bool Scheduler::step()
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
    else if (pre)
    {
        rQ->enque(currNode);
        currNode = NULL;
    }
    return false;
}
void Scheduler::display(ofstream *fileOut)
{
    *fileOut << "*********************************************************\n";
    *fileOut << "FCFS Summary (WT = wait time, TT = turnaround time):\n\n";
    *fileOut << "PID\t\tWT\t\tTT" << endl;
    float twAve = 0, ttaAve = 0;
    for (int i = 0; i < rQ->reqQue->nR; i++)
    {
        fQ[i]->display(fileOut);
        twAve += fQ[i]->tw;
        ttaAve += fQ[i]->tta;
    }
    twAve /= rQ->reqQue->nR;
    ttaAve /= rQ->reqQue->nR;

    *fileOut << "AVG\t\t" << twAve << "\t" << ttaAve << endl
             << endl;
}