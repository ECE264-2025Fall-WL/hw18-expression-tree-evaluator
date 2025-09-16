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
    // if the allocation fails, print an error message end exit(1)
    // hint: use fprintf to print the error message in the stderr stream


    /* Write your code below */


    /**************************************************************/

    // step b: copy the token into node->data
    // hint: use strncpy with a limit of MAX_TOKEN - 1, for safer copying (syntax provided in assignment description)

    /* Write your code below */


    
    // ensuring null termination
    node->data[MAX_TOKEN - 1] = '\0';

    /**************************************************************/

    // step c: initialize left and right children to NULL

    /* Write your code below */

    
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
            // case (a): token is a number (not an operator)
            // - create a leaf node using the createNode() function you just implemented
            // - push the node into the stack

            /* Write your code below */


        }
        else {
            Node* right;
            Node* left;
            Node* operator;
            // case (b): token is an operator
            // 1. pop right node from the stack then pop the left node 
            // Note: use the given right and left nodes

                /* Write your code below */
        


            
            // 2. create a new node for the operator using the createNode() function 
            // - connect to it the left and right node
            // - push the operator node into the stack
            // Note: use the given operator node
            
                /* Write your code below */





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
            - Recursive case (operator node): evaluate left and right and apply operator

            Notes:  - Division is integer division (default in C).
                    - We will assume that all division expressions 
                      are non-zero for simplicity.

     */

     if(!root){
        fprintf(stderr, "evaluate: null node encountered\n");
        exit(1);
     }

    // Base case: if data in root is a number (not an operator)
    // hint1: use the isOperator() function

    if(/* Replace this comment with your code */){
    
    // - return the number
    // hint2: convert the string to int using the atoi() function
         
    /* Write your code below */

    }
    else {
        // Recursive case: if in root is an operator (use the variables given below)
        int leftVal;
        int rightVal;
        char operator = root->data[0]; // because ex: "+" is "+\0"

        // - recursively evaluate left node
            /* Write your code below */


        // - recursively evaluate right node
            /* Write your code below */


        // - return the result based on the operator
        // hint: use switch case for the operator for the following cases (+, -, *, /)
            /* Write your code below */

    }

   return -1;
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
