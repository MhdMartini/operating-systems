#ifndef MMU_H
#define MMU_H
#include <vector>
#include "clock.h"

class MMU
{
public:
    MMU(int mSize, int dSize, int pSize);
    std::vector<int> pStart = {0}; // the start address in pages for each process

public:
    int pSize;   // page size
    int mSize;   // main memory size
    int dSize;   // disk size
    int nFrames; // number of pages

public:
    bool *bitMap;    // which main memory frames are free
    bool **bitTable; // valid, reference, and dirty bits for pages
    int *fTable;     // frame number, indexed by page number

public:
    char *mem;  // main memory
    char *disk; // disk

    Clock *clock;

public:
    void initMem();
    int recReq(const char OP, int id, int vAdd, int val); // receive read request from processes
    int getpNumber(int id, int vAdd);                     // get page number from virtual address
    int getPTE(int pid, int vAdd);                        // get index in page table entry
    int getOffset(int vAdd);                              // get offset in page
    int getGAdd(int pte);                                 // get global address
    int read(int memAdd);                                 // read four bytes from valid memory address as integer (BE)
    void write(int memAdd, int value);                    // write four bytes integer into valid memory address (BE)
    int getFFrame();                                      // get first free frame
    ~MMU();
};

#endif