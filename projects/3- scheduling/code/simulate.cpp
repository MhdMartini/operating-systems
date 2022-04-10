#include "scheduler.h"
#include <fstream>

void simulateFCFS(char *fileIn, char *fileOut, int interval)
{
    Scheduler sch(fileIn, "FCFS");
    ofstream myfile;
    myfile.open(fileOut);
    myfile << "***** FCFS Scheduling *****\n";
    bool done = false;
    int t = 0;
    do
    {
        done = sch.step();
        if (!(t % interval))
            sch.report(&myfile);
        t++;
    } while (!done);
    myfile << "\n*********************************************************\n";
    sch.summary(&myfile);
    myfile.close();
}