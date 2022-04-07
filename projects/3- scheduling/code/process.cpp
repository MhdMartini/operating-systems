#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include "process.h"

using namespace std;

int READY = 0;
int RUNNING = 1;
int FINISHED = 2;

Process::Process(int pid, int burstTime, int priority, int arrivalTime)
{
    id = pid;
    tb = burstTime;
    pr = priority;
    ta = arrivalTime;
    taub = tb;
}
void Process::wait()
{
    tta++;
    tw++;
}
bool Process::burst()
{
    tta++;
    taub--;
    return (taub == 0);
}

void Process::display()
{
    cout << "PID:\t\t\t" << id << endl;
    cout << "Burst Time:\t\t" << tb << endl;
    cout << "Priority:\t\t" << pr << endl;
    cout << "Arrival Time:\t\t" << ta << endl;
    cout << "Rem. Burst Time:\t" << taub << endl;
    cout << "Waiting Time:\t\t" << tw << endl;
    cout << "Turnaround Time:\t" << tta << endl;
}

PNode::PNode(Process *process)
{
    p = process;
}
void PNode::display()
{
    cout << "Wrapper node for process:" << endl;
    p->display();
}

void argsFromRow(int *tb, int *pr, int *ta, std::string row)
/* get process three integer arguments from space separated row */
{
    std::stringstream rowStream(row);
    int value;
    int idx = 0;
    int args[3];
    while (rowStream >> value)
    {
        args[idx] = value;
        idx++;
        if (idx == 3)
        {
            *tb = args[0];
            *pr = args[1];
            *ta = args[2];
        }
    }
}

PNode *pNodeFromRow(int pid, std::string row)
{
    int tb, ta, pr;
    argsFromRow(&tb, &pr, &ta, row);
    Process *p = new Process(pid, tb, pr, ta);
    PNode *pNode = new PNode(p);
    return pNode;
}

Process *pCopy(Process *p)
{
    int pid = p->id;
    int tb = p->tb;
    int ta = p->ta;
    int pr = p->pr;
    int taub = p->taub;

    int tw = p->tw;
    int tta = p->tta;
    Process *p2 = new Process(pid, tb, pr, ta);
    p2->taub = taub;
    p2->tw = tw;
    p2->tta = tta;
    return p2;
}

PNode *pNodeCopy(PNode *pNode)
{
    Process *p2 = pCopy(pNode->p);
    PNode *pNode2 = new PNode(p2);
    return pNode2;
}