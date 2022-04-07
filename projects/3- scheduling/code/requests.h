#ifndef REQUESTS_H
#define REQUESTS_H

#include "process.h"

class Requests
{
private:
    char *fileIn;
    PNode *head = NULL;
    int t = 0;

    void initQue(void); // store requests as sorted linked list
    void enque(PNode &pNode);

public:
    Requests(char *fileIn);
    void display();
};

#endif