#ifndef PROCESS_H
#define PROCESS_H
#include "mmu.h"
#include <thread>
#include <mutex>

class Process
{
public:
    Process(MMU *mmu, int id, const char *fileThread, int pSize);
    Process(int id, const char *fileThread, int pSize);
    FILE *fIn; // pointer to input file
    void init();

public:
    MMU *mmu;                // send requests to this MMU
    int id;                  // process id
    int pSize;               // page size
    int vMSize;              // virtual memory size
    int nPages;              // number of pages
    int *regs = new int[32]; // 32 registers

public:
    void senReq(const char OP, int regNum, int vAdd); // send read and write request to MMU
    void start();                                     // start thread
    std::thread getThread();                          // ge thread that points to start()
    ~Process();

private:
    void statusStart();                                              // print start status
    void statusOp(const char OP, int regNum, int vAdd);              // print request status
    void statusReq(const char OP, int regNum, int retVal, int vAdd); // print read or write status
    void statusComplete();                                           // print complete status
};

#endif