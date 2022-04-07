#ifndef READY_QUE_H
#define READY_QUE_H
#include "requests.h"

class ReadyQue
{
private:
    Requests *reqQue = NULL; // requests buffer
    PNode *head = NULL;

public:
    ReadyQue(Requests *requests);
    void display(void);
    void step(void);          // enque requests of t according to scheme, and wait
    void enque(PNode *pNode); // enque according to scheme
    PNode *pop(void);         // pop a process to burst it
    void wait(void);          // make all processes wait
};

#endif