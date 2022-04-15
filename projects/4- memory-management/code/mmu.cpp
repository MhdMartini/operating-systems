#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "mmu.h"

#define VALID 0
#define REFERENCE 1
#define DIRTY 2

extern std::mutex lockFile, lockMMU;

MMU::MMU(int mSize, int dSize, int pSize)
    : mSize(mSize), dSize(dSize), pSize(pSize) { initMem(); }
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
        fTable[i] = -1;
    }
}
int MMU::recReq(const char OP, int id, int vAdd, int val)
{
    // /* receive read or write request from process */

    return 25;
}
void MMU::display()
{
    std::cout << "MMU: " << std::endl;
    std::cout << "mSize: " << mSize << std::endl;
    std::cout << "dSize: " << dSize << std::endl;
    std::cout << "pSize: " << pSize << std::endl;
    std::cout << "nFrames: " << nFrames << std::endl;
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