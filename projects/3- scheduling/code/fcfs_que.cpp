#include <stdio.h>
#include <iostream>
#include "scheduler_ques.h"

using namespace std;

void FCFS::enque(PNode *pNode)
{
    /* FCFS: append to end of list */
    // cout << "here" << endl;
    if (head == NULL)
    {
        head = pNode;
        return;
    }

    PNode *currPNode = head;
    PNode *lastPNode = NULL;
    while (currPNode != NULL)
    {
        lastPNode = currPNode;
        currPNode = currPNode->next;
    }
    lastPNode->next = pNode;
}

void SJF::enque(PNode *pNode)
{
    /* SJF/STCF: insert according to taub */
    // if (head == NULL)
    // {
    //     head = pNode;
    //     return;
    // }

    // PNode *currPNode = head;
    // PNode *lastPNode = NULL;
    // while ((currPNode != NULL) || (currPNode->p->taub > pNode->p->taub))
    // {
    //     lastPNode = currPNode;
    //     currPNode = currPNode->next;
    // }
    // if (lastPNode != NULL)
    //     lastPNode->next = pNode;
    // else
    //     head = pNode;
    if (head == NULL)
    {
        head = pNode;
        return;
    }

    PNode *currPNode = head;
    PNode *lastPNode = NULL;
    while (currPNode != NULL)
    {
        lastPNode = currPNode;
        currPNode = currPNode->next;
    }
    lastPNode->next = pNode;
}