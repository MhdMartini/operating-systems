#ifndef MMU_H
#define MMU_H
#include <vector>

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

public:
    void initMem();
    int recReq(const char OP, int id, int vAdd, int val); // receive read request from processes
    void display();
    ~MMU();
};

#endif