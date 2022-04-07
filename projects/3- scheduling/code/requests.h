#ifndef REQUESTS_H
#define REQUESTS_H

#include "process.h"

class Requests
{
private:
    char *fileIn;
    PNode *head = NULL;
    int t = 0;
    int end = 0;
    bool done = false;

    void initQue(void);
    void enque(PNode &pNode);

public:
    Requests(char *fileIn);
    void display();
    void displayT();
    int step();
};

#endif