#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(char *fileIn, string name)
{
    fIn = fileIn;
    NAME = name;
    initRqQ();
    deque<Process *> fQ(nR);
}
void Scheduler::initRqQ()
{
    ifstream myfile;
    myfile.open(fIn);
    string line;
    int pid = 0;
    while (getline(myfile, line))
    {
        deque<int> lineData;
        stringstream lineStream(line);
        int value;
        while (lineStream >> value)
            lineData.push_back(value);

        Process *p = new Process(pid, lineData[0], lineData[1], lineData[2]);
        rqQ.push_back(p);
        pid++;
        nR++;
    }
    myfile.close();
    return;
}
void Scheduler::loadRQ()
{
    /* move incoming requests from request que to ready que.
    requests are added with the enqueRQ method which depends
    on the scheduler protocol*/
    while (1)
    {
        if (rqQ.empty())
            break;

        if (rqQ[0]->ta == t)
        {
            // move to ready que; continue
            enqueRQ(rqQ[0]);
            rqQ.pop_front();
            continue;
        }
        else if (rqQ[0]->ta < t)
            continue;
        else
            break;
    }
}
void Scheduler::enqueRQ(Process *p)
{
    rQ.push_back(p);
}
bool Scheduler::step()
{
    statusTime();
    loadRQ();
    bool done = false;
    if (runPro != NULL)
    {
        if (runPro->burst())
        {
            fQ.push_back(runPro);
            statusFinishing();
            if (load())
                done = true;
            else
                statusFinishingLoading();
        }
        else
            statusRunning();
    }
    else
    {
        load(); // first iteration
        statusLoading();
    }
    waitRQ();
    statusRQ();
    t++;
    return done;
}
bool Scheduler::load()
{
    // if you can load, change runPro, else keep it
    if (rQ.empty())
        return true;

    runPro = rQ.front();
    rQ.pop_front();
    return false;
}
void Scheduler::waitRQ()
{
    for (auto x : rQ)
        x->wait();
}
void Scheduler::statusTime()
{
    status = "t = ";
    status += to_string(t);
    status += "\n";
}
void Scheduler::statusLoading()
{
    status += "CPU: Loading process ";
    status += to_string(runPro->id);
    status += " (CPU burst = ";
    status += to_string(runPro->tb);
    status += ")";
    conSwi++;
    proSeq += to_string(runPro->id) + "-";
}
void Scheduler::statusFinishing()
{
    status += "CPU: Finishing process ";
    status += to_string(runPro->id);
}
void Scheduler::statusFinishingLoading()
{
    status += "; loading process ";
    status += to_string(runPro->id);
    status += " (CPU burst = ";
    status += to_string(runPro->tb);
    status += ")";
    conSwi++;
    proSeq += to_string(runPro->id) + "-";
}
void Scheduler::statusRunning()
{
    status += "CPU: Running process ";
    status += to_string(runPro->id);
    status += " (remaining CPU burst = ";
    status += to_string(runPro->taub);
    status += ")";
}
void Scheduler::statusRQ()
{
    status += "\nReady que: ";
    size_t len = rQ.size();
    if (len == 0)
        status += "empty\n";

    for (int i = 0; i < len; i++)
    {
        status += to_string(rQ[i]->id);
        if (i == len - 1)
            status += "\n";
        else
            status += "-";
    }
}
void Scheduler::report(ofstream *myfile)
{
    *myfile << status << endl;
}
void Scheduler::summary(ofstream *myfile)
{
    sortfQ(); // sort fQ by arrival time
    *myfile << NAME << " Summary (WT = wait time, TT = turnaround time):\n\n";
    *myfile << "PID\t\tWT\t\tTT\n";
    float twAve = 0, ttaAve = 0;
    for (auto p : fQ)
    {
        *myfile << " " << p->id << "\t\t" << p->tw << "\t\t" << p->tta << endl;
        twAve += p->tw;
        ttaAve += p->tta;
    }
    *myfile << "AVG\t\t" << twAve / nR << "\t" << ttaAve / nR << "\n\n";
    proSeq.pop_back();
    *myfile << proSeq << endl;
    *myfile << "Context switches: " << to_string(conSwi) << endl;
}
void Scheduler::sortfQ()
{
    // sort ready que by arrival time
    for (int i = 0; i < fQ.size(); i++)
    {
        for (int j = 0; j < fQ.size() - 1; j++)
        {
            if (fQ[j]->ta > fQ[j + 1]->ta)
            {
                Process *temp = fQ[j];
                fQ[j] = fQ[j + 1];
                fQ[j + 1] = temp;
            }
        }
    }
}
Scheduler::~Scheduler()
{
    for (auto x : rqQ)
        delete x;
    for (auto x : rQ)
        delete x;
    for (auto x : fQ)
        delete x;
}