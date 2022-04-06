#include <stdio.h>
#include <iostream>
#include "process.h"

using namespace std;

int READY = 0;
int RUNNING = 1;
int FINISHED = 2;

Process::Process(int pid, int burstTime, int arrivalTime, int priority)
{
    id = pid;
    tb = burstTime;
    ta = arrivalTime;
    p = priority;
    taub = tb;
    display();
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
    cout << "PID:\t\t" << id << endl;
    cout << "Burst Time:\t" << tb << endl;
    cout << "Arrival Time:\t" << ta << endl;
    cout << "Priority:\t" << p << endl;
    cout << "Rem. Burst Time: " << taub << endl;
}