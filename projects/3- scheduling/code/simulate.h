#ifndef SIMULATE_H
#define SIMULATE_H
#include "process.h"
#include <fstream>
#include <deque>
#include <string>

void simulateFCFS(char *fileIn, char *fileOut, int interval);
void simulateSJF(char *fileIn, char *fileOut, int interval);
void simulatePriority(char *fileIn, char *fileOut, int interval);
void simulateSTCF(char *fileIn, char *fileOut, int interval);
void simulateRR(char *fileIn, char *fileOut, int interval);
#endif