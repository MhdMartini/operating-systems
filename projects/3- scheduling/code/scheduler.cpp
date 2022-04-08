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
void Scheduler::simulate(void)
{
    /*
    1- step the ready que
    2- burst node, if null pop it
    */

    PNode *pNode = NULL;
    do
    {
        rQ->step();
        pNode = rQ->pop();
        cout << "Loaded Process " << pNode->p->id << endl;
        bool pDone = false;
        while (!pDone)
        {
            rQ->wait();
            pDone = pNode->p->burst();
            rQ->step();
        }
        // add to finished que
        cout << "Done with Process " << pNode->p->id << endl;
        pNode->display();
    } while (pNode->next != NULL);
}