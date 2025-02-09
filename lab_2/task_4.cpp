#include <iostream>
using namespace std;

struct node
{
    int data;
    node* next;
};

int main(void)
{
    // linked list is zero-indexed
    node start = {};
    node* cursor = &start;

    for (int i = 0; i < 10; i++)
    {
        cursor -> data = i;
        cursor -> next = new node;
        cursor = cursor -> next;
        cursor -> next = nullptr;
    }

    cursor = &start;
    while (cursor -> next)
    {   
        cout << cursor -> data << endl;
        cursor = cursor -> next;
    }

    return 0;
}
