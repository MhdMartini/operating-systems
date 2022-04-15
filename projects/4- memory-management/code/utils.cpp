#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "utils.h"

#define INT_SIZE 4
#define BYTE_SIZE 8

#define LOG(x) std::cout << x << std::endl
#define LOGH(x) std::cout << std::hex << x << std::endl

int read(char *address)
{
    /* read four bytes from valid memory address as integer */
    uint8_t temp;
    int n = 0;
    for (int i = 0; i < INT_SIZE; i++)
    {
        temp = (uint8_t)address[i];
        n = (n << BYTE_SIZE) | temp;
    }
    return n;
}
void write(char *address, int value)
{
    /* write four bytes integer into valid memory address */
    int temp, n = 0;
    for (int i = INT_SIZE - 1; i > -1; i--)
    {
        temp = value & 0x0000FF;
        address[i] = (char)temp;
        value = value >> BYTE_SIZE;
    }
}

void start_processes(std::vector<Process *> &processes, MMU *mmu)
{
    /* give processes their mmu and locks, get their threads,
    and start and join the threads */
    std::vector<std::thread> threads;
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i]->mmu = mmu;
        threads.push_back(processes[i]->getThread());
    }
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    for (int i = 0; i < processes.size(); i++)
    {
        delete processes[i];
    }
    delete mmu;
}

void run(char *fileName)
{
    /* read memory size, page size from file. create processes
    and read their vMSize to get the disk size.
    create mmu, pass it to processes and start processes*/
    std::ifstream infile(fileName);
    int mSize, pSize, nPro, dSize = 0;
    infile >> mSize >> pSize >> nPro;

    std::string fileThread;
    std::vector<Process *> processes;
    for (int i = 0; i < nPro; i++)
    {
        infile >> fileThread;
        fileThread = fileThread;
        const char *fileThreadCh = (const char *)fileThread.c_str();
        Process *p = new Process(i, fileThreadCh, pSize);
        dSize += p->vMSize;
        processes.push_back(p);
    }
    infile.close();

    MMU *mmu = new MMU(mSize, dSize, pSize);
    start_processes(processes, mmu);
}