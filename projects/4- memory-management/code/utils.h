#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <thread>
#include "process.h"
#include "mmu.h"

int read(char *mem);                  // read four bytes from valid memory address as integer
void write(char *address, int value); // write four bytes integer into valid memory address

void start_processes(std::vector<Process *> &processes, MMU *mmu);
void run(char *fileIn, char*fileOut); // given input file name, create objects and start execution

#endif