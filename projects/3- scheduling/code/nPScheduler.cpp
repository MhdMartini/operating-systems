#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "scheduler.h"

using namespace std;
void FCFS::enqueRQ(Process *p) { rQ.push_back(p); }
void SJF::enqueRQ(Process *p)
{
    // add to ready que
    rQ.push_back(p);
    sortQ(rQ, [](Process *p) -> int
          { return (p->tb); });
    return;
}
void Priority::enqueRQ(Process *p)
{
    // add to ready que
    rQ.push_back(p);
    sortQ(rQ, [](Process *p) -> int
          { return (p->pr); });
    return;
}