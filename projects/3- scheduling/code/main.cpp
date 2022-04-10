#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "process.h"
#include "scheduler.h"

using namespace std;

int main(int argc, char *argv[])
{
    char *fileIn = argv[1];
    char *fileOut = argv[2];
    int interval = atoi(argv[3]);

    Scheduler sch(fileIn, "FCFS");
    ofstream myfile;
    myfile.open(fileOut);
    myfile << "***** FCFS Scheduling *****\n";
    bool done = false;
    do
    {
        done = sch.step();
        if (!((sch.t - 1) % interval))
            sch.report(&myfile);
    } while (!done);
    sch.summary(&myfile);

    myfile.close();

    return 0;
}