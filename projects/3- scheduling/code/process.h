#ifndef PROCESS_H
#define PROCESS_H

#include <string>

extern int READY;
extern int RUNNING;
extern int FINISHED;

class Process
{
public:
    int id;   // process id
    int tb;   // burst time
    int ta;   // time of arrival
    int pr;   // priority
    int taub; // remaining burst time

    int tw = 0;  // waiting time
    int tta = 0; // turnaround time

    Process(int pid, int burstTime, int priority, int arrivalTime);
    void display();
    void wait();
    bool burst();
};

class PNode
/* wrapper node for a process which points to the next
node in line */
{
public:
    Process *p;
    PNode *next = NULL;

    PNode(Process *process);
    void display();
};

void argsFromRow(int *tb, int *p, int *ta, std::string row);
PNode *pNodeFromRow(int pid, std::string row);
PNode *pNodeCopy(PNode *pNode);

#endif