#include <stdlib.h>
#include "stack.h"

void push(struct stack *this, int x)
{
    struct stack *current = this;
    while (current->next)
        current = current->next;

    struct stack *newnode = malloc(sizeof(struct stack));
    newnode->data = x;
    newnode->next = NULL;

    current->next = newnode;
}

int pop(struct stack *this)
{
    struct stack *current = this;
    struct stack *previous = current;

    while (current->next)
    {
        previous = current;
        current = current->next;
    }
    int top = current->data;
    previous->next = NULL;
    //  The next pointer of previous points to NULL means the current node is no longer in the stack
    free(current);
    return top;
}

struct stack *new_stack()
{ /*top of stack init a meaning less space.
   ,delete_stack(struct stack*) will free it*/
    struct stack *stk = malloc(sizeof(struct stack));
    stk->data = 0;
    stk->next = NULL;
    return stk;
}

void delete_stack(struct stack *stk)
{
    free(stk);
}