#ifndef SCHEDULER_STATS_H
#define SCHEDULER_STATS_H
#include "scheduler.h"

void simulate(Scheduler *sch, char *fileOut, int interval);
void printLoading(std::ofstream *fileOut, Process *p);
void printPreemting(std::ofstream *fileOut, Process *pIn, Process *pOut);
void printFinishingLoading(std::ofstream *fileOut, Process *pIn, Process *pOut);
void printRunning(std::ofstream *fileOut, Process *p);
void printFinishing(std::ofstream *fileOut, Process *p);
#endif