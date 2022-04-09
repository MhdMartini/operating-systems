#ifndef SCHEDULER_STATS_H
#define SCHEDULER_STATS_H
#include "scheduler.h"

void simulate(char *fileIn, char *fileOut, int interval);
void printLoading(std::ofstream *myfile, Process *p);
void printPreemting(std::ofstream *myfile, Process *pIn, Process *pOut);
void printFinishingLoading(std::ofstream *myfile, Process *pIn, Process *pOut);
void printRunning(std::ofstream *myfile, Process *p);
void printFinishing(std::ofstream *myfile, Process *p);
#endif