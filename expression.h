#include <stdio.h>

#ifndef EXPR_H
#define EXPR_H

#define MAX_TOKEN 50
#define MAX_EXPR 100

typedef struct Node {
    char data[MAX_TOKEN];
    struct Node *left, *right;
} Node;

typedef struct {
    Node* arr[MAX_EXPR];
    int top;
} Stack;


// Stack functions
void initStack(Stack *s);
int isEmpty(Stack *s);
void push(Stack *s, Node *node);
Node* pop(Stack *s);


int isOperator(const char *s);


// Tree functions
Node* createNode(char *data);
Node* buildExpressionTree(char *tokens[], int n);
int evaluate(Node *root);
void printInfix(Node *root, FILE *out);
void freeTree(Node *root);

#endif
