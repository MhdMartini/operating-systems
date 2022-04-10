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
    myfile << "*********************************************************\n";
    sch.summary(&myfile);
    myfile.close();
}
void overallSummary(deque<Scheduler *> &stats, char *fileOut)
{
    ofstream myfile;
    myfile.open(fileOut, ofstream::out | ofstream::app);
    myfile << "***** OVERALL SUMMARY *****\n\n";

    myfile << "Wait Time Comparison\n";
    sortStats(stats, [](Scheduler *s) -> int
              { return (s->twAve); });
    for (int i = 0; i < stats.size(); i++)
        myfile << i + 1 << " " << stats[i]->NAME << "\t\t" << stats[i]->twAve << "\n";
    myfile << "\n";

    myfile << "Turnaround Time Comparison\n";
    sortStats(stats, [](Scheduler *s) -> int
              { return (s->ttaAve); });
    for (int i = 0; i < stats.size(); i++)
        myfile << i + 1 << " " << stats[i]->NAME << "\t\t" << stats[i]->ttaAve << "\n";
    myfile << "\n";

    myfile << "Context Switch Comparison\n";
    sortStats(stats, [](Scheduler *s) -> int
              { return (s->conSwi); });
    for (int i = 0; i < stats.size(); i++)
        myfile << i + 1 << " " << stats[i]->NAME << "\t\t" << stats[i]->conSwi << "\n";
    myfile.close();
}

int main(int argc, char *argv[])
{
    char *fileIn = argv[1];
    char *fileOut = argv[2];
    int interval = atoi(argv[3]);
    int quantum = 2;

    deque<Scheduler *> stats;

    FCFS fcfs(fileIn, "FCFS");
    simulate(fcfs, fileOut, interval);
    stats.push_back(&fcfs);

    SJF sjf(fileIn, "SJF");
    simulate(sjf, fileOut, interval);
    stats.push_back(&sjf);

    STCF stcf(fileIn, "STCF");
    simulate(stcf, fileOut, interval);
    stats.push_back(&stcf);

    RR rr(fileIn, "RR", quantum);
    simulate(rr, fileOut, interval);
    stats.push_back(&rr);

    Priority priority(fileIn, "PRIO");
    simulate(priority, fileOut, interval);
    stats.push_back(&priority);

    overallSummary(stats, fileOut);

    return 0;
}