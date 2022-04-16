#ifndef CLOCK_H
#define CLOCK_H

class Node
{
public:
    Node(int pid, int pNumber, int pte);
    int pid, pNumber;
    int pte;
    Node *next = nullptr;
};

class Clock
{
public:
    Clock();
    Node *head;
    Node *hand;
    Node *tail;

public:
    void enque(int pid, int pNumber, int pte);   // enqueue a new node
    void replace(int pid, int pNumber, int pte); // replace the node pointed at by hand to the new node
    Node *step();                                // move the hand to the next node
};

#endif