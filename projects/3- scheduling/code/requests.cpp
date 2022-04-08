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
    // display();
}
void Requests::initQue(void)
{
    /* read requests from input file and store them as a
    linked list sorted by time of arrival */
    ifstream myfile;
    myfile.open(fileIn);

    std::string row;
    int pid = 0;
    while (std::getline(myfile, row))
    {
        PNode *pNode = pNodeFromRow(pid, row);
        enque(*pNode);
        pid++;
        nR++;
    }
    len = nR;
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
int Requests::step(void)
{
    /* move head to the end, and find the new end */
    PNode *currPNode = head;
    for (int i = 0; i < end; i++)
    {
        head = currPNode->next;
        currPNode = head;
        len--;
    }

    // count requests from head to t
    end = 0;
    while ((currPNode != NULL) && (currPNode->p->ta <= t))
    {
        currPNode = currPNode->next;
        end++;
    }
    t++;
    return end;
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
void Requests::displayT()
{
    PNode *node = head;
    int myEnd = end;
    while (myEnd--)
    {
        node->display();
        node = node->next;
    }
}