#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "requests.h"
#include "ready_que.h"

using namespace std;

ReadyQue::ReadyQue(Requests *requests, const string name)
{
    reqQue = requests;
    head = NULL;
    NAME = name;
}
void ReadyQue::wait(void)
{
    /* make all processes in ready que wait */
    PNode *currPNode = head;
    while (currPNode != NULL)
    {
        currPNode->p->wait();
        currPNode = currPNode->next;
    }
}
PNode *ReadyQue::pop(void)
{
    /* pop the head and change head to its next */
    PNode *currPNode = head;
    if (currPNode == NULL)
        return NULL;
    head = head->next;
    return currPNode;
}
void ReadyQue::enque(PNode *pNode) { return; }
void ReadyQue::step(void)
{
    /* step requests que and enque accordingly */
    int rt = reqQue->step();
    PNode *currPNode = reqQue->head;
    for (int i = 0; i < rt; i++)
    {
        PNode *currPNodeCopy = pNodeCopy(currPNode);
        enque(currPNodeCopy);

        currPNode = currPNode->next;
    }
}
void ReadyQue::display(ofstream *fileOut)
{
    /* display all nodes in the queue */
    *fileOut << "Ready queue: ";
    if (head == NULL)
    {
        *fileOut << "empty" << endl;
        return;
    }

    PNode *node = head;
    while (node != NULL)
    {
        *fileOut << node->p->id;
        if (node->next == NULL)
            *fileOut << endl;
        else
            *fileOut << "-";
        node = node->next;
    }
}