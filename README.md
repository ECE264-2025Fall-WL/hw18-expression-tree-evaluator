# 🧮 Expression Tree Evaluator

This project builds, prints, and evaluates arithmetic expressions using a **binary expression tree**.  
You will parse **postfix expressions** (Reverse Polish Notation), build an expression tree, and then use recursion to evaluate and print it.

---

## 📚 Learning Goals

By completing this assignment, you will:

- Understand **expression notations**: infix, prefix, postfix (RPN).
- Learn how to convert **postfix → expression tree** using a stack.
- Use **recursion** to traverse and evaluate binary trees.
- Practice **dynamic memory management** (`malloc`, `free`).
- Work with **file I/O** in C (`fopen`, `fclose`, `fscanf`, `fprintf`).
- Organize code with **separate compilation** (`stack.c`, `tree.c`, `expression.h`).
- Test and debug using a **Makefile** with automated test cases.

---

## 🔑 Background Concepts

### Expression Notations
- **Infix**: operators between operands  
  Example: `(3 + 4) * 5`
- **Postfix (RPN)**: operators after operands  
  Example: `3 4 + 5 *`
- **Prefix**: operators before operands  
  Example: `* + 3 4 5`

👉 Postfix is easy for computers because order of evaluation is explicit — no parentheses needed.

### What is `tokens`?
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

## 📦 The Stack (provided in `stack.c`)

The **stack** is already implemented for you. It is used to build the expression tree from postfix input.

### 🔎 How the stack works
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

#### 2. `Node* pop(Stack *s)`
- Removes and returns the node from the **top** of the stack.  
- You will use this when handling an operator: pop the right operand first, then the left operand.  

#### 3. `bool isEmpty(Stack *s)`
- Returns `true` if the stack has no elements, `false` otherwise.  
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

## 🧩 Your Task in `tree.c`

Students need to implement **three functions**:

### 1. `createNode()`
```c
Node* createNode(const char *token);
```
- Allocate memory for a new node.
- Copy the `token` string into the node.
- Initialize left and right children to `NULL`.

**Write your code below the comment markers:**
```c
// write your code here
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
// replace this comment with your code
```

---

### 3. `evaluate()`
```c
int evaluate(Node *root);
```
- Recursively evaluate the expression tree.

#### Algorithm
1. If the node is a **leaf** → convert its string value to an integer (use `atoi()`) and return it.  
2. If the node is an **operator**:  
   - Recursively evaluate the left child → `leftVal`.  
   - Recursively evaluate the right child → `rightVal`.  
   - Apply the operator (`+`, `-`, `*`, `/`) to combine the results.  
   - Return the computed value.  

#### Pseudocode Example
```
function evaluate(node):
    if node is NULL:
        return 0
    
    if node is a leaf (no children):
        return integer value of node->token
    
    leftVal = evaluate(node->left)
    rightVal = evaluate(node->right)
    
    if node->token == "+":
        return leftVal + rightVal
    else if node->token == "-":
        return leftVal - rightVal
    else if node->token == "*":
        return leftVal * rightVal
    else if node->token == "/":
        return leftVal / rightVal
```

---

## 🖨️ Printing and Freeing the Tree

These are already implemented for you:
- `printInfix(Node *root, FILE *out);`
- `void freeTree(Node *root);`

You do **not** need to change them.

---

## 🖥️ Main Program

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

## 🧪 Testing Your Program

A Makefile is provided.

### Build
```bash
make
```

### Run one test
```bash
make test1
```
Which runs:
```bash
./expr tests/test1.txt output1
diff -u expected/expected1.txt output1
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

## 📂 Example Files

### `tests/test1.txt`
```
3 4 + 5 *
```

### `expected/expected1.txt`
```
(3 + 4) * 5 = 35
```

---

## 📦 Submission Requirements

Submit only:
```
tree.c
```

Zip and upload:
```bash
zip hw18.zip tree.c
```

Do **not** submit `main.c`, `stack.c`, or the Makefile — they’re provided.

---

## ⚡ Key Takeaways

- `tokens` is the **postfix expression split into strings**.  
- `createNode()` builds nodes for operands/operators.  
- `buildExpressionTree()` uses the **stack** to combine nodes.  
- `evaluate()` recursively computes the value of the expression tree.  
- You only edit `tree.c`, under the **"write your code here"** markers.  
- The rest of the code (stack, printing, freeing) is already done for you.

---
