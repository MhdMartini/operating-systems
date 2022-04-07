#ifndef REQUESTS_H
#define REQUESTS_H

#include "process.h"

class Requests
{
private:
    char *fileIn;

    void initQue(void);       // create sorted linked list by arrival time
    void enque(PNode &pNode); // insert PNode to que according to arrival time

public:
    int t = 0; // keep time

    PNode *head = NULL; // head PNode
    int len = 0;        // number of remaining requests
    int end = 0;        // number of requests to be enqueued by ready que

    Requests(char *fileIn);
    void display();  // show all nodes in que
    void displayT(); // show all nodes available at time t
    int step();      // move head to end, find and return new end
};

#endif