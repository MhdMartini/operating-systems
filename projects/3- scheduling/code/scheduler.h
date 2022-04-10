#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"
#include <fstream>
#include <deque>
#include <string>

using namespace std;

class Scheduler
{
private:
    char *fIn;
    char *fOut;

public:
    int t = 0;                            // time step
    int nR = 0;                           // number of requests
    float twAve = 0;                      // average waiting time
    float ttaAve = 0;                     // average turnaround time
    int conSwi = 0;                       // number of context switches
    int qua;                              // quantum time for RR
    string proSeq = "Process sequence: "; // process sequence string

    deque<Process *> rqQ;   // requests que
    deque<Process *> rQ;    // ready que
    deque<Process *> fQ;    // finished que
    string NAME;            // scheduler name
    string status;          // scheduler status string
    Process *runPro = NULL; // running process

    Scheduler(char *fileIn, string name, int quantum = 2);
    void initRqQ();                                          // add requests to requests que
    void loadRQ();                                           // load incoming requests to ready que
    virtual void enqueRQ(Process *p);                        // add a process to ready que
    void sortQ(deque<Process *> &Q, int (*func)(Process *)); // sort a queue according to members' attribute
    bool load();                                             // load a process from rQ
    virtual bool step();                                     // load burst preempt and finish
    void waitRQ();                                           // wait processes in ready que

    /* methods to update status string */
    void statusTime();
    void statusLoading();
    void statusAndLoading();
    void statusRunning();
    void statusFinishing();
    void statusPreempting();
    void statusRQ();
    void report(ofstream *fileOut);
    void summary(ofstream *fileOut);

    ~Scheduler(); // destructor
};
class FCFS : public Scheduler
{
    using Scheduler::Scheduler;
    void enqueRQ(Process *p);
};
class SJF : public Scheduler
{
    using Scheduler::Scheduler;
    void enqueRQ(Process *p);
};
class Priority : public Scheduler
{
    using Scheduler::Scheduler;
    void enqueRQ(Process *p);
};
class STCF : public Scheduler
{
    using Scheduler::Scheduler;
    void enqueRQ(Process *p);
    bool step();
};
class RR : public Scheduler
{
    using Scheduler::Scheduler;
    void enqueRQ(Process *p);
    bool step();
};

void sortStats(deque<Scheduler *> &stats, int (*att)(Scheduler *)); // sort a deque of finished schedulers according to attribute
#endif