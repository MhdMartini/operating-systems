#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include "process.h"

using namespace std;

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
void Process::display(ofstream *fileOut)
{
    /* PID  WT  TT */
    *fileOut << " " << id << "\t\t" << tw << "\t\t" << tta << endl;
}
