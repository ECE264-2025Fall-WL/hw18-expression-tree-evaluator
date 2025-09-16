/// DO NOT MODIFY THIS FILE ///

#include <stdio.h>
#include <stdlib.h>
#include "expression.h"

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return (s->top == -1);
}

// Push a node pointer onto the stack
void push(Stack *s, Node *node) {
    if (s->top == MAX_EXPR - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    s->arr[++(s->top)] = node;
}

// Pop a node pointer from the stack
Node* pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return s->arr[(s->top)--];
}
