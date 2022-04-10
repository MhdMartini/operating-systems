#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "scheduler.h"
#include "scheduler.h"

using namespace std;

void simulate(Scheduler &sch, char *fileOut, int interval)
{
    ofstream myfile;
    myfile.open(fileOut, ofstream::out | ofstream::app);
    myfile << "***** " << sch.NAME << " Scheduling *****\n";
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

int main(int argc, char *argv[])
{
    char *fileIn = argv[1];
    char *fileOut = argv[2];
    int interval = atoi(argv[3]);
    int quantum = 2;

    FCFS fcfs(fileIn, "FCFS");
    simulate(fcfs, fileOut, interval);

    SJF sjf(fileIn, "SJF");
    simulate(sjf, fileOut, interval);

    Priority priority(fileIn, "Priority");
    simulate(priority, fileOut, interval);

    STCF stcf(fileIn, "STCF");
    simulate(stcf, fileOut, interval);

    RR rr(fileIn, "RR", quantum);
    simulate(rr, fileOut, interval);

    return 0;
}