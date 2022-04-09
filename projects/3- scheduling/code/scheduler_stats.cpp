#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"
#include <fstream>
using namespace std;

void simulate(char *fileIn, char *fileOut, int interval)
{
    Requests reqQue(fileIn);
    FCFS fcfs(&reqQue);
    Scheduler sch(&fcfs);

    ofstream myfile;
    myfile.open(fileOut);
    myfile << "***** FCFS Scheduling *****" << endl;

    Process *currP = NULL;
    Process *lastP = NULL;
    int t = 30;
    bool done = false;
    while (!sch.step())
    {
        t = sch.rQ->reqQue->t - 1;

        lastP = currP;
        currP = sch.currProcess;

        if (t % interval)
            continue;

        myfile << "t = " << t << endl;
        if (lastP != currP)
        {
            // loading / finishing / preempting
            if (lastP == NULL)
                // loading
                myfile << "CPU: Loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
            else
            {
                // finishing / preempting
                if (lastP->taub > 0)
                {
                    // preempting
                    myfile << "CPU: Preempting process " << lastP->id << " (remaining CPU burst = " << lastP->taub << "); ";
                    myfile << "loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
                }
                else
                {
                    // finishing and loading
                    myfile << "CPU: Finishing process " << lastP->id << "; ";
                    myfile << "loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
                }
            }
        }
        else
            // running
            myfile << "CPU: Running process " << currP->id << " (remaining CPU burst = " << currP->taub + 1 << ")" << endl;
        myfile << endl;
    }
    myfile << "t = " << ++t << endl;
    myfile << "CPU: Finishing process " << currP->id << endl;

    cout << "Good bye!" << endl;
    myfile.close();
}