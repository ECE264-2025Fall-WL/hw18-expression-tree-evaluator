#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expression.h"

#define MAX_TOKEN 50
#define MAX_EXPR 100

int isOperator(const char *s) {
    return (s && s[1] == '\0' && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'));
}


Node* createNode(char *data) {
    /*
    1) CreateNode: Allocate and initialize a node.
       Steps:
               a) allocate memory
               b) copy token "operand or operator" into node->data
               c) initialize node children to NULL
    */

    Node* node;

    // step a: allocate memory for one node
    // if the allocation fails, print print an error message end exit(1)
    // hint: use fprintf to print the error message in the stderr stream


    /* Write your code here */
    node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for Node\n");
        exit(1);
    }

    /**************************************************************/

    // step b-1: copy the token into node->data
    // hint: use strncpy with a limit of MAX_TOKEN - 1, for safer copying
    // step b-2: ensure null termination by replacing the '\n' with '\0'

    /* Write your code here */
    strncpy(node->data, data, MAX_TOKEN - 1);
    node->data[MAX_TOKEN - 1] = '\0';
    
    /**************************************************************/

    // step c: initialize children to NULL

    /* Write your code here */
    node->left  = NULL;
    node->right = NULL;
    
    /**************************************************************/

    return node;

}

Node* buildExpressionTree(char *tokens[], int n) {
    /*
    2) buildExpressionTree: Build a binary expression tree from a postfix token array.
        Steps:
                a) if token is a number: create node, push it into the stack
                b) if token is an operator: 
                        - pop right
                        - pop left
                        - make operator the root of left and right
                        - push it
    */

    Stack st;
    initStack(&st);

    // iterating over each token in the expression
    for(int i = 0; i < n; i++){
        char *token = tokens[i];
        
        if(!isOperator(token)){
            Node *leafNode;
            // case (a): is a number (not an operator)
            // create a leaf node and push it into the stack

            /* Write your code here */
            leafNode = createNode(token);
            push(&st, leafNode);

        }
        else {
            Node* right;
            Node* left;
            Node* operator;
            // case (b): is an operator
            // 1. pop right node from the stack then pop the left node

                /* Write your code here */
                right = pop(&st);
                left = pop(&st);

            // 2. create a new node for the operator
            // - connect to it the left and right node
            // - push the operator node into the stack
                
                /* Write your code here */
                operator = createNode(token);
                operator->left = left;
                operator->right = right;

                push(&st, operator);

        }
    }
    
    // now the stack should have only one node which is the root node of the expression tree
    Node* root = pop(&st);

    return root;
}
int evaluate(Node *root) {
     /*
        3) evaluate recursively:
            - Base case (number node): return number
            - Recursive case (operator node): evaulate left and right and apply operator

            Notes:  - Division is integer division (default in C).
                    - We will assume that all division expressions 
                      are non-zero for simplicity.

     */

     if(!root){
        fprintf(stderr, "evaluate: null node encountered\n");
        exit(1);
     }

     // Base case: if root is a number (not an operator), return the number
     // hint1: use the isOperator() function
     // hint2: convert the string to int using the atoi() function

         /* Write your code here */
         if(!isOperator(root->data)){
            return atoi(root->data);
         }


    // Recursive case: if root is an operator
    int leftVal;
    int rightVal;
    char operator = root->data[0]; // because ex: "+" is "+\0"

    // - recursively evaluate left node
        /* Write your code here */
        leftVal = evaluate(root->left);

    // - recursively evaluate right node
        /* Write your code here */
        rightVal = evaluate(root->right);

    // - return the result based on the operator
    // hint: use switch case for the operator for following cases (+, -, *, /)
        /* Write your code here */
    switch(operator){
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    
    
    return -1;

}
// void printInfix(Node *root, FILE *out) {
//      /* ... */ 
//     }
void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
