#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"

using namespace std;

void STCF::enqueRQ(Process *p)
{
    rQ.push_back(p);
    sortQ(rQ, [](Process *p) -> int
          { return (p->taub); });
    return;
}
bool STCF::step()
{
    // step logic
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
                statusAndLoading();
        }
        else if ((!rQ.empty()) && ((rQ.front()->taub < runPro->taub)))
        {
            enqueRQ(runPro);
            statusPreempting();
            load();
            statusAndLoading();
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

void RR::enqueRQ(Process *p) { rQ.push_back(p); }
bool RR::step()
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
                statusAndLoading();
        }
        else if ((!rQ.empty()) && (!(t % qua)))
        {
            enqueRQ(runPro);
            statusPreempting();
            load();
            statusAndLoading();
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