#include <iostream>

using namespace std;

class Node
{
public:
    int number;
    Node *next;
};

void insert(Node *head, int val)
{
    Node *ptr = head;
    while ((ptr->next != NULL))
    {
        ptr = ptr->next;
    }
    Node *newNode = new Node;
    newNode->number = val;
    ptr->next = newNode;
}

Node *listFromArray(int arr[5], int size)
{
    Node *head = new Node;
    head->number = 0;
    head->next = NULL;
    for (int i = 1; i < size; i++)
    {
        insert(head, arr[i]);
    }
    return head;
}

void printList(Node *head)
{
    Node *ptr = head;
    while ((ptr != NULL))
    {
        cout << ptr->number << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

int main()
{
    int nums[5] = {0, 1, 2, 3, 4};
    Node *head = listFromArray(nums, 5);
    printList(head);

    return 0;
}
