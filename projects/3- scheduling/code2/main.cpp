/*
Process
    - holds process-related information
    - process helpful functions:
        * burst
        * wait

PNode
    - process node class to hold a process and point to a next process
    - used by requests que to sort requests by arrival time

Requests
    - reads and stores all requests from file
    - sorts the requests according to arrival time as a linked list
    - step method:
        updates the end and len attributes:
            * end tells us how many requests to read at a give time
            * len tells us how many requests remain.

ReadyQue

*/

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
    myfile << "***** FCFS Scheduling *****\n\n";
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

    return 0;
}