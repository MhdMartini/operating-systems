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
    return 1;
}