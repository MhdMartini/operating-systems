#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include "mainfunc.h"

using namespace std;

/* given a filename containing newline separated integers,
 return a vector of these integers */
vector<int> intVectorFromFile(string fileName)
{
    std::ifstream myFile(fileName);
    std::vector<int> myQueue;
    int val;
    while (myFile >> val)
    {
        myQueue.push_back(val);
    }
    return myQueue;
}

// convert a vector into a stack
stack<int> queueToStack(vector<int> queue)
{
    stack<int> myStack;
    for (auto x : queue)
        myStack.push(x);
    return myStack;
}

// insert a new node to a linked list of integers
void insertNode(MyNode **root, int number)
{
    MyNode *currNode = new MyNode;
    MyNode *ptr;
    currNode->number = number;
    currNode->next = NULL;

    if (*root == NULL)
        *root = currNode;
    else
    {
        ptr = *root;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = currNode;
    }
}

// convert a vector into a linked list
MyNode *vectorToLinkedList(vector<int> queue)
{
    MyNode *root = NULL;
    for (auto x : queue)
        insertNode(&root, x);
    return root;
}

// print content of a vector
void printVector(vector<int> myQueue)
{
    for (auto x : myQueue)
        cout << x << " ";
    cout << endl;
}

// print content of a stack
void printStack(stack<int> myStack)
{
    while (!myStack.empty())
    {
        cout << myStack.top() << " ";
        myStack.pop();
    }
    cout << endl;
}

// print content of a linked list
void printLinkedList(MyNode *root)
{
    while (root != NULL)
    {
        cout << root->number << " ";
        root = root->next;
    }
    cout << endl;
}