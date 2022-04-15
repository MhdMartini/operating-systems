#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mmu.h"
#include "process.h"

#define LOG(x) std::cout << x << std::endl
#define LOGH(x) std::cout << std::hex << x << std::endl

using namespace std;

void start_processes(std::vector<Process *> &processes, MMU *mmu)
{
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i]->mmu = mmu;
        processes[i]->start();
        delete processes[i];
    }
    delete mmu;
}

void test(char *fileName)
{
    /* read memory size, page size from file. create processes
    and read their vMSize to get the disk size.
    create mmu, pass it to processes and start processes*/
    std::ifstream infile(fileName);
    int mSize, pSize, nPro, dSize = 0;
    infile >> mSize;
    infile >> pSize;
    infile >> nPro;

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

int main(int argc, char *argv[])
{
    test(argv[1]);
    return 0;
}