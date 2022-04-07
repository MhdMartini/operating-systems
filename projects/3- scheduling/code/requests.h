#ifndef REQUESTS_H
#define REQUESTS_H

#include "process.h"

class Requests
{
private:
    char *fileIn;
    PNode *head = NULL;
    int t = 0;

public:
    Requests(char *fileIn);
    void init(void); // store requests as sorted linked list
    void display();
};

#endif