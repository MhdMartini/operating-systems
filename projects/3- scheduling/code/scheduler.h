#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"
#include <fstream>
#include <deque>
#include <string>

using namespace std;

class Scheduler
{
public:
    char *fIn;
    char *fOut;
    int nR = 0;
    int t = 0;
    int conSwi = 0;                       // number of context switches
    string proSeq = "Process sequence: "; // process sequence

    deque<Process *> rqQ;
    deque<Process *> rQ;
    deque<Process *> fQ;
    string NAME;
    string status;
    Process *runPro = NULL;

    Scheduler(char *fileIn, string name);
    void initRqQ();                   // add requests to requests que
    void loadRQ();                    // load incoming requests to ready que
    virtual void enqueRQ(Process *p); // add a process to ready que
    bool load();                      // load a process from rQ
    virtual bool step();              // load burst and finish
    void waitRQ();                    // wait process in ready que

    /* methods to update status string */
    void statusTime();
    void statusLoading();
    void statusAndLoading(bool future = false);
    void statusRunning();
    void statusFinishing();
    void statusPreempting();
    void statusRQ();
    void report(ofstream *fileOut);
    void summary(ofstream *fileOut);
    void sortQ(deque<Process *> &Q, int (*func)(Process *));
    ~Scheduler();
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
#endif