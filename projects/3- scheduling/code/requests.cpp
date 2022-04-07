/*
class to simulate incoming requests from processes
    - it saves all requests from input text file as a linked
    list sorted by time of arrival.
    - it has a head and an end int indicating the number of requests
    at time t. At every step call, the head and end are updated according
    to the time step and queue content.
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "requests.h"
#include "process.h"

using namespace std;

Requests::Requests(char *fileInput)
{
    fileIn = fileInput;
    initQue();
    display();
}
void Requests::initQue(void)
{
    /* read requests from input file and store them as a
    linked list sorted by time of arrival */
    ifstream myfile;
    myfile.open(fileIn);

    std::string row;
    int pid = 1;
    while (std::getline(myfile, row))
    {
        PNode *pNode = pNodeFromRow(pid, row);
        enque(*pNode);
        pid++;
    }

    myfile.close();
    return;
}
void Requests::enque(PNode &pNode)
{
    /* enque next row from file according to time of arriva,
    lines in input file could be out of order */
    PNode *lastPNode = NULL;
    PNode *currPNode = head;
    while (1)
    {
        if ((currPNode == NULL) || (pNode.p->ta < currPNode->p->ta))
        {
            if (currPNode == head)
                head = &pNode;
            break;
        }
        lastPNode = currPNode;
        currPNode = currPNode->next;
    }

    pNode.next = currPNode;
    if (lastPNode != NULL)
        lastPNode->next = &pNode;
}
void Requests::display()
{
    /* display all nodes in the queue */
    PNode *node = head;
    while (node != NULL)
    {
        node->display();
        node = node->next;
    }

    cout << fileIn << endl;
}