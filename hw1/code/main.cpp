#include <stdio.h>
#include <algorithm>
#include <iostream>
#include "mainfunc.h"

using namespace std;

int main(int argc, char **argv)
{
    // read the input filename into an std vector (queue structure), and store its size
    vector<int> myQueue = intVectorFromFile(argv[1]);
    int length = myQueue.size();

    // create stack structure
    stack<int> myStack = queueToStack(myQueue);

    /* create the linked list structure from the queue.
    first copy myQueue to a another vector and sort it */
    std::vector<int> sortedQueue = myQueue;
    sort(sortedQueue.begin(), sortedQueue.end());

    // convert the sorted vector to a linked list
    MyNode *root = vectorToLinkedList(sortedQueue);

    // print structures
    cout << "QUEUE CONTENTS:" << endl;
    printVector(myQueue);

    cout << "STACK CONTENTS:" << endl;
    printStack(myStack);

    cout << "LIST CONTENTS:" << endl;
    printLinkedList(root);

    return 0;
}
