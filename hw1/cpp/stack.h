#ifndef __STACK_H__
#define __STACK_H__

class Node
{
    int data;

public:
    struct Node *next;
    Node(int x) : data(x), next(nullptr) {}
    int getData()
    {
        return data;
    }
};

class Stack
{
    Node *top;

public:
    Stack();
    void push(int x);
    int pop();
    ~Stack();
};

#endif