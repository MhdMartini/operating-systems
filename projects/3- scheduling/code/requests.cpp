/*
class to simulate incoming requests from processes
    - it saves all requests from input text file as a linked
    list sorted by time of arrival.
    - it maintains a counter, each time its step function is
    called, its head is updated to the first request at time
    <= t
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
    init();
    display();
}
void Requests::init(void)
{
    /* read requests from input file and store them as a
    linked list sorted by time of arrival */
    ifstream myfile;
    myfile.open(fileIn);

    std::string row;
    int pid = 0;
    int n;

    PNode *lastPNode = NULL;
    while (std::getline(myfile, row))
    {
        /*
        1- make a pnode out of a string row
            if head is NULL make it head
        2- make this node last pnode's (if not NULL) next
        */
        PNode *pNode = pNodeFromRow(pid, row);
        if (head == NULL)
            head = pNode;

        if (lastPNode != NULL)
            lastPNode->next = pNode;

        lastPNode = pNode;
        pid++;
    }

    myfile.close();
    return;
}
void Requests::display()
{
    PNode *node = head;
    while (node != NULL)
    {
        node->display();
        node = node->next;
    }

    cout << fileIn << endl;
}