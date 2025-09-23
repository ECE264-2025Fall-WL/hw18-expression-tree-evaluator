# Expression Tree Evaluator

This assignment builds, prints, and evaluates arithmetic expressions using a **binary expression tree**.
A binary expression tree evaluator is a program that constructs a binary tree from a postfix arithmetic expression and computes its result by recursively evaluating the tree, where operands are stored in the leaves and operators are stored in the internal nodes (will be explained in the below sections).

---

## Learning Goals

By completing this assignment, you will:

- Understand **expression notations**: infix, prefix, postfix (RPN).
- Learn how to convert **postfix → expression tree** using a stack.
- Use **recursion** to traverse and evaluate binary trees.
- Practice **dynamic memory management** `malloc()`.

---

## Background Concepts

### Expression Notations
- **Infix**: operators between operands  
  Example: `(3 + 4) * 5`
- **Postfix (RPN)**: operators after operands  
  Example: `3 4 + 5 *`
- **Prefix**: operators before operands  
  Example: `* + 3 4 5`

- Postfix is easy for computers because the order of evaluation is explicit — no parentheses needed.
---
### What are `tokens`?
- `tokens` is an **array of strings** read from the input file.  
- Each element is one **operand** (like `3`, `x`) or one **operator** (like `+`, `*`).  
- Example: if the file contains:
  ```
  3 4 + 5 *
  ```
  then:
  ```c
  tokens[0] = "3"
  tokens[1] = "4"
  tokens[2] = "+"
  tokens[3] = "5"
  tokens[4] = "*"
  count = 5
  ```

---
### Expression Tree
An **expression tree** is a binary tree where:
- **Leaves** = operands (numbers/variables).
- **Internal nodes** = operators.

Example for `3 4 + 5 *`:

```
       *
      / \
     +   5
    / \
   3   4
```
#### **You can use this tool to help you visualize the examples:** https://notation-visualizer.ajayliu.com/

### The Stack (provided in `stack.c`)

The **stack** is already implemented for you. It is used to build the expression tree from postfix input.

#### How the stack works
A stack is a **Last-In, First-Out (LIFO)** data structure.  
- Imagine a stack of plates: you can only add (push) to the top, and remove (pop) from the top.  
- Example sequence:
  1. Push `3`
  2. Push `4`
  3. Pop → removes `4`
  4. Pop → removes `3`

This is exactly how we manage operands and operators when building an expression tree.

### Provided functions
```c
void push(Stack *s, Node *node);
Node* pop(Stack *s);
bool isEmpty(Stack *s);
```

#### 1. `push(Stack *s, Node *node)`
- Places a node on **top** of the stack.  
- You will use this when you encounter an operand (number/variable) or a newly created operator node.
- Example:
  ```c
  Node* node = createNode(5);
  push(&stack, node);
  ```

#### 2. `Node* pop(Stack *s)`
- Removes and returns the node from the **top** of the stack.  
- You will use this when handling an operator: pop the right operand first, then the left operand.
- Example:
  ```c
  Node* node = pop(&stack);
  ``` 

#### 3. `int isEmpty(Stack *s)`
- Returns `1` if the stack has no elements, `0` otherwise.  
- You can use this as a safeguard to make sure you don’t pop from an empty stack.

### Usage in building the tree
1. **Push operands** (numbers) directly as nodes.  
2. When you see an **operator**:
   - Pop the **right operand**.
   - Pop the **left operand**.
   - Create a new operator node with these as children.
   - Push the new node back.  

At the end, the stack will contain **one node**: the root of the expression tree.

---

## Your Task in `tree.c`

Students need to implement **three functions**:

### 1. `createNode()`
```c
Node* createNode(const char *token);
```
- Allocate memory for a new node.
- Copy the `token` string into the node.

  **Note:** You will need to use the `strncpy()` function (for safer copying).
  ```c
  char *strncpy(char *dest, const char *src, size_t n);
  ```
    - `dest` → destination buffer (where the string will be copied to).
    - `src` → source string (the string to copy).
    - `n` → maximum number of characters to copy.
- Initialize left and right children to `NULL`.

**Write your code below the comment markers:**
```c
/* Write your Code below */
```
**OR replace the following comment marker with your code**
```c
/* Replace this comment with your code */
```
---

### 2. `buildExpressionTree()`
```c
Node* buildExpressionTree(char *tokens[], int count);
```
- Use the stack functions (`push`, `pop`) to build the tree.
- Algorithm:
  1. Loop over all tokens.
  2. If operand → `createNode()` → push.
  3. If operator → pop right, pop left → `createNode(op)` → attach children → push.
  4. After loop, pop once → root.

**Write your code below the comment markers:**
```c
/* Write your Code below */
```
**OR replace the following comment marker with your code**
```c
/* Replace this comment with your code */
```
---

### 3. `evaluate()`
```c
int evaluate(Node *root);
```
- Recursively evaluate the expression tree.
**Note:** You will need to use the `atoi()` function (for converting a string to an integer).
```c
int atoi(const char *str);
```

- Initialize left and right children to `NULL`.
#### Algorithm
1. If the node is a **leaf** → convert its string value to an integer (use `atoi()`) and return it.  
2. If the node is an **operator**:  
   - Recursively evaluate the left child → `leftVal`.  
   - Recursively evaluate the right child → `rightVal`.  
   - Apply the operator (`+`, `-`, `*`, `/`) to combine the results.  
   - Return the computed value.  

**Write your code below the comment markers:**
```c
/* Write your Code below */
```
**OR replace the following comment marker with your code**
```c
/* Replace this comment with your code */
```

### Example
For `(3 + 4) * 5`:
- Left: `3 + 4 = 7`
- Right: `5`
- Multiply: `7 * 5 = 35`

Output:
```
35
```
---

## Main Program

`main.c` is provided and does the following:

1. Reads filenames from command-line args:
   ```bash
   ./expr input.txt output.txt
   ```
2. Reads tokens (postfix expression) from `input.txt`.
3. Calls your `buildExpressionTree()`.
4. Prints the infix form and evaluation to `output.txt`.
5. Frees all memory with `freeTree()`.

---

## Testing Your Program

A Makefile is provided.

### Build
```bash
make
```

### Run one test
```bash
make test1
```

### Run all tests
```bash
make testall
```

### Memory check (Valgrind on Linux/Mac)
```bash
make memory
```

---

## Example Files

### `tests/test2.txt`
```
3 4 + 5 *
```

### `expected/expected2.txt`
```
35
```

---

## Submission Requirements

Submit only:
```
tree.c
```

Do **not** submit `main.c`, `stack.c`, or the Makefile — they’re provided.

---

## Key Takeaways

- `tokens` is the **postfix expression split into strings**.  
- `createNode()` builds nodes for operands/operators.  
- `buildExpressionTree()` uses the **stack** to combine nodes.  
- `evaluate()` recursively computes the value of the expression tree.  
- You only edit `tree.c`, under the **"write your code here"** markers.  
- The rest of the code (stack, printing, freeing) is already done for you.

---

## Worked Example Trace

Expression:  
```
5 6 2 + * 12 4 / -
```

1. Push `5`.  
2. Push `6`.  
3. Push `2`.  
4. See `+` → pop `2, 6` → make `(6 + 2)` node → push.  
5. See `*` → pop `(6 + 2), 5` → make `(5 * (6 + 2))` node → push.  
6. Push `12`.  
7. Push `4`.  
8. See `/` → pop `4, 12` → make `(12 / 4)` node → push.  
9. See `-` → pop `(12 / 4), (5 * (6 + 2))` → make `((5 * (6 + 2)) - (12 / 4))` node → push.  

Final tree:  
```
         -
       /   \
      *     /
     / \   / \
    5  + 12   4
      / \
     6   2
```

Evaluation:
- `(6 + 2) = 8`  
- `5 * 8 = 40`  
- `12 / 4 = 3`  
- `40 - 3 = 37`  

Output:
```
37
```
 
