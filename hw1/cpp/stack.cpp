#include "stack.h"
Stack::Stack()
{
    top = new Node(0);
}
void Stack::push(int x)
{
    Node *newnode = new Node(x);
    Node *current = top;
    while (current->next)
        current = current->next;

    current->next = newnode;
}

int Stack::pop()
{
    Node *current = top;
    Node *previous = current;

    while (current->next)
    {
        previous = current;
        current = current->next;
    }

    int top_data = current->getData();
    previous->next = nullptr;
    delete current;
    return top_data;
}
Stack::~Stack()
{
    delete top;
}