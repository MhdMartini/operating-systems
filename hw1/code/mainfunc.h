#ifndef MAINFUNC_H
#define MAINFUNC_H

#include <vector>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class MyNode
{
public:
    int number;
    MyNode *next;
};

vector<int> intVectorFromFile(string fileName);
stack<int> queueToStack(vector<int> queue);
void insertNode(MyNode **root, int item);
MyNode *vectorToLinkedList(vector<int> queue);

void printVector(vector<int> queue);
void printStack(stack<int> myStack);
void printLinkedList(MyNode *root);

#endif