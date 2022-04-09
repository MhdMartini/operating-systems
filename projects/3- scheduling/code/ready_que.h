#ifndef READY_QUE_H
#define READY_QUE_H
#include "requests.h"

class ReadyQue
{
public:
    Requests *reqQue = NULL; // requests buffer
    PNode *head = NULL;

    ReadyQue(Requests *requests);
    void step(void);                  // enque requests of t according to scheme, and wait
    virtual void enque(PNode *pNode); // enque according to scheme
    PNode *pop(void);                 // pop a process to burst it
    void wait(void);                  // make all processes wait
    void display(std::ofstream *fileOut);
};

#endif