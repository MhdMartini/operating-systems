#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "clock.h"

Node::Node(int pid, int pNumber, int pte) : pid(pid), pNumber(pNumber), pte(pte) {}

Clock::Clock() {}
void Clock::enque(int pid, int pNumber, int pte)
{
    Node *newNode = new Node(pid, pNumber, pte);
    if (head == nullptr)
    {
        head = newNode;
        hand = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}
void Clock::replace(int pid, int pNumber, int pte)
{
    // replace the node pointed at by hand to the new node
    hand->pid = pid;
    hand->pNumber = pNumber;
    hand->pte = pte;
}
Node *Clock::step()
{
    // move the hand to the next node
    hand = hand->next;
    if (hand == nullptr)
        hand = head;
    return hand;
}