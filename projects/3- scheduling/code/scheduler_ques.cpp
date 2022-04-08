#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "scheduler_ques.h"

using namespace std;

void FCFS::enque(PNode *pNode)
{
    /* enque as FCFS basis */
    if (head == NULL)
    {
        head = pNodeCopy(pNode);
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