#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "requests.h"
#include "ready_que.h"

using namespace std;

ReadyQue::ReadyQue(Requests *requests)
{
    reqQue = requests;
    head = NULL;
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
void ReadyQue::display(void)
{
    /* display all nodes in the queue */
    PNode *node = head;
    while (node != NULL)
    {
        node->display();
        node = node->next;
    }
}