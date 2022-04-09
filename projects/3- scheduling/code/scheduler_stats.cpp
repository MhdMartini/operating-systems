#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"
#include "scheduler_stats.h"
#include <fstream>

using namespace std;

void simulate(char *fileIn, char *fileOut, int interval)
{
    Requests reqQue(fileIn);
    FCFS fcfs(&reqQue);
    Scheduler sch(&fcfs);

    ofstream myfile;
    myfile.open(fileOut, ofstream::out | ofstream::app);
    myfile << "***** FCFS Scheduling *****" << endl;

    Process *currP = NULL;
    Process *lastP = NULL;
    int t;
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
                printLoading(&myfile, currP);
            else
            {
                // finishing / preempting
                if (lastP->taub > 0)
                    // preempting
                    printPreemting(&myfile, lastP, currP);
                else
                    // finishing and loading
                    printFinishingLoading(&myfile, currP, lastP);
            }
        }
        else
            // running
            printRunning(&myfile, currP);

        // display ready que
        fcfs.display(&myfile);
        myfile << endl;
    }
    myfile << "t = " << ++t << endl;
    printFinishing(&myfile, currP);
    fcfs.display(&myfile);
    myfile << endl;
    // show summary

    myfile.close();
}

void printLoading(ofstream *fileOut, Process *p)
{
    *fileOut << "CPU: Loading process " << p->id << " (CPU burst = " << p->tb << ")" << endl;
}
void printPreemting(ofstream *fileOut, Process *pIn, Process *pOut)
{
    *fileOut << "CPU: Preempting process " << pOut->id << " (remaining CPU burst = " << pOut->taub << "); ";
    *fileOut << "loading process " << pIn->id << " (CPU burst = " << pIn->tb << ")" << endl;
}
void printFinishingLoading(ofstream *fileOut, Process *pIn, Process *pOut)
{
    *fileOut << "CPU: Finishing process " << pOut->id << "; ";
    *fileOut << "loading process " << pIn->id << " (CPU burst = " << pIn->tb << ")" << endl;
}
void printRunning(ofstream *fileOut, Process *p)
{
    *fileOut << "CPU: Running process " << p->id << " (remaining CPU burst = " << p->taub + 1 << ")" << endl;
}
void printFinishing(ofstream *fileOut, Process *p)
{
    *fileOut << "CPU: Finishing process " << p->id << endl;
}