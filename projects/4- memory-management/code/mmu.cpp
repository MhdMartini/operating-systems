#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>
#include "mmu.h"

#define VALID 0
#define REFERENCE 1
#define DIRTY 2
#define INT_SIZE 4
#define BYTE_SIZE 8

extern std::mutex lockFile, lockMMU, lockDisk, lockFault, lockAll;

MMU::MMU(int mSize, int dSize, int pSize, std::vector<int> &pStart)
    : mSize(mSize), dSize(dSize), pSize(pSize), pStart(pStart)
{
    initMem();
    clock = new Clock();
}
void MMU::initMem()
{
    mem = new char[mSize];
    disk = new char[dSize];
    bitMap = new bool[nFrames];
    bitTable = new bool *[nFrames];
    fTable = new int[nFrames];
    for (int i = 0; i < nFrames; i++)
    {
        bitMap[i] = true;
        bitTable[i] = new bool[3];
        memset(bitTable[i], 0, 3);
        fTable[i] = -1;
    }
}
int MMU::recReq(const char OP, int id, int vAdd, int val)
{
    lockAll.lock();
    // get pte for requested address
    int pNumber = getpNumber(id, vAdd);
    int pte = getPTE(id, pNumber);

    // pte valid, store or read and return
    if (bitTable[pte][VALID])
    {
        int fNum = fTable[pte];
        int offset = getOffset(vAdd);
        int memAdd = fNum * pSize + offset;

        bitTable[pte][REFERENCE] = true;
        if (OP == 'R')
            val = read(memAdd);
        else
        {
            bitTable[pte][DIRTY] = true;
            write(memAdd, val);
        }
        lockAll.unlock();
        return val;
    }

    // invalid page, look for empty frame
    int fFrame = getFFrame();

    // if no empty frame, step the clock until frame-to-evict is found
    if (fFrame == -1)
    {
        int pteVictim;
        Node *canVic;
        while (1)
        {
            canVic = clock->step();
            pteVictim = getPTE(canVic->pid, canVic->pNumber);
            if (!bitTable[pteVictim][REFERENCE])
                break;
            bitTable[pteVictim][REFERENCE] = false;
        }

        // mark it invalid
        bitTable[pteVictim][VALID] = false;

        // get its address in disk
        fFrame = fTable[pteVictim];
        int memAdd = fFrame * pSize;
        int diskAdd = pteVictim * pSize;

        // store frame in disk
        std::memcpy(disk + diskAdd, mem + memAdd, pSize);

        // replace clock node
        clock->replace(id, pNumber, pte);

        // bring the page from disk to mem
        diskAdd = pte * pSize;
        std::memcpy(mem + memAdd, disk + diskAdd, pSize);

        // modify the new pte (set valid bit, reset reference bit, store frame number)
        bitTable[pte][VALID] = true;
        bitTable[pte][REFERENCE] = false;
        fTable[pte] = fFrame;

        lockAll.unlock();
        return -1;
    }

    // free frame found, bring the page from disk to mem
    int memAdd = fFrame * pSize;
    int diskAdd = pte * pSize;
    std::memcpy(mem + memAdd, disk + diskAdd, pSize);

    // modify the new pte (set valid bit, enqueue clock node, store frame number)
    bitTable[pte][VALID] = true;
    fTable[pte] = fFrame;
    clock->enque(id, pNumber, pte);

    lockAll.unlock();
    return -1;
}
int MMU::getpNumber(int id, int vAdd) { return vAdd / pSize; }
int MMU::getPTE(int pid, int pNum) { return pStart[pid] + pNum; }
int MMU::getOffset(int vAdd) { return vAdd % pSize; }
int MMU::getGAdd(int pte) { return pte * pSize; }
int MMU::read(int memAdd)
{
    /* read four bytes from valid memory address as integer */
    uint8_t temp;
    int n = 0;
    for (int i = 0; i < INT_SIZE; i++)
    {
        temp = (uint8_t)mem[i];
        n = (n << BYTE_SIZE) | temp;
    }
    return n;
}
void MMU::write(int memAdd, int value)
{
    /* write four bytes integer into valid memory address (BE) */
    int temp, n = 0;
    for (int i = INT_SIZE - 1; i > -1; i--)
    {
        temp = value & 0x0000FF;
        mem[i] = (char)temp;
        value = value >> BYTE_SIZE;
    }
}
int MMU::getFFrame()
{
    /* get first free frame */
    for (int i = 0; i < nFrames; i++)
    {
        if (bitMap[i])
        {
            bitMap[i] = false;
            return i;
        }
    }
    return -1;
}

MMU::~MMU()
{
    delete[] mem;
    delete[] disk;
    for (int i = 0; i < nFrames; i++)
    {
        delete[] bitTable[i];
    }
    delete[] bitTable;
    delete[] bitMap;
    delete[] fTable;
}