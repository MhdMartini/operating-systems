#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "process.h"

extern std::mutex lockFile, lockMMU;

Process::Process(MMU *mmu, int id, std::string fileThread, int pSize)
    : mmu(mmu), id(id), fileThread(fileThread), pSize(pSize) {}
Process::Process(int id, std::string fileThread, int pSize)
    : id(id), fileThread(fileThread), pSize(pSize) {}

void Process::start()
{
    /* parse thread file to decide number of pages and send requests*/
    statusStart();
    FILE *fp = fopen((const char *)fileThread.c_str(), "r");
    fscanf(fp, "%d ", &vMSize);
    nPages = vMSize / pSize;
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
    std::cout << "Process " << id << " started" << std::endl;
    lockFile.unlock();
}
void Process::statusOp(const char OP, int regNum, int vAdd)
{
    // P0 OPERATION: R r0 0
    lockFile.lock();
    std::cout << "Process " << id << " "
              << "OPERATION: " << OP << " r" << regNum << " " << vAdd << std::endl;
    lockFile.unlock();
}
void Process::statusReq(const char OP, int regNum, int retVal, int vAdd)
{
    // print read or write requests
    lockFile.lock();
    std::cout << "P" << id << ": ";
    if (OP == 'R')
    {
        std::cout << "r" << regNum
                  << " = 0x" << std::setfill('0') << std::setw(8) << std::hex << retVal << " ("
                  << "mem at virtual addr 0x"
                  << std::setfill('0') << std::setw(8) << std::hex
                  << vAdd << ")" << std::endl;
    }
    else
    {
        std::cout << "mem at virtual addr 0x"
                  << std::setfill('0') << std::setw(8) << std::hex << vAdd
                  << " = 0x" << std::setfill('0') << std::setw(8) << std::hex << retVal
                  << " (r" << regNum << ")" << std::endl;
    }
    lockFile.unlock();
}
void Process::statusComplete()
{
    lockFile.lock();
    std::cout << "Process " << id << " complete" << std::endl;
    lockFile.unlock();
}

Process::~Process() { delete[] regs; }