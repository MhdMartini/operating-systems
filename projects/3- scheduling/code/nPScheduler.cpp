#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "scheduler.h"

using namespace std;

void SJF::enqueRQ(Process *p)
{
    // add to ready que
    rQ.push_back(p);
    sortQ(rQ, [](Process *p) -> int
          { return (p->tb); });
    return;
}