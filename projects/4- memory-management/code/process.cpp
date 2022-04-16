#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "process.h"

extern std::mutex lockFile, lockMMU;

Process::Process(MMU *mmu, int id, std::string fileThread, int pSize)
    : mmu(mmu), id(id), fileThread(fileThread), pSize(pSize) { init(); }
Process::Process(int id, std::string fileThread, int pSize)
    : id(id), fileThread(fileThread), pSize(pSize) { init(); }
void Process::init()
{
    FILE *fp = fopen((const char *)fileThread.c_str(), "r");
    fscanf(fp, "%d ", &vMSize);
    nPages = vMSize / pSize;
    fclose(fp);
}

void Process::start()
{
    /* parse thread file to decide number of pages and send requests*/
    statusStart();
    FILE *fp = fopen((const char *)fileThread.c_str(), "r");
    fscanf(fp, "%d ", &vMSize);
    while (!feof(fp))
    {
        int regNum, vAdd;
        char OP, _;
        fscanf(fp, "%c %c%d %d ", &OP, &_, &regNum, &vAdd);
        statusOp(OP, regNum, vAdd);
        senReq(OP, regNum, vAdd);
    }
    fclose(fp);
    statusComplete();
}
std::thread Process::getThread()
{
    return std::thread(&Process::start, this);
}
void Process::senReq(const char OP, int regNum, int vAdd)
{
    /* send write or read request to MMU. if -1 is received, send same request*/
    int retVal = -1;
    while (retVal == -1)
        retVal = mmu->recReq(OP, id, vAdd, regs[regNum]);

    if (OP == 'R')
        regs[regNum] = retVal;
    statusReq(OP, regNum, retVal, vAdd);
}

void Process::statusStart()
{
    lockFile.lock();
    fprintf(mmu->fOut, "Process %d: started\n", id);
    lockFile.unlock();
}
void Process::statusOp(const char OP, int regNum, int vAdd)
{
    // P0 OPERATION: R r0 0
    lockFile.lock();
    fprintf(mmu->fOut, "Process %d OPERATION: %c r%d %d\n", id, OP, regNum, vAdd);
    lockFile.unlock();
}
void Process::statusReq(const char OP, int regNum, int retVal, int vAdd)
{
    // print read or write requests
    lockFile.lock();
    if (OP == 'R')
        fprintf(mmu->fOut, "P%d: r%d = 0x%.8X (mem at virtual addr 0x%.8X)\n", id, regNum, retVal, vAdd);
    else
        fprintf(mmu->fOut, "P%d: mem at virtual addr 0x%.8X = 0x%.8X (r%d)\n", id, vAdd, retVal, regNum);
    lockFile.unlock();
}
void Process::statusComplete()
{
    lockFile.lock();
    fprintf(mmu->fOut, "Process %d complete\n", id);
    lockFile.unlock();
}

Process::~Process() { delete[] regs; }