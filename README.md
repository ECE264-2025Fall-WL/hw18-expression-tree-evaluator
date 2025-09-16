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

Available functions:
```c
void push(Node *n);
Node* pop(void);
bool isEmpty(void);
```

How to use:
1. **Push operands** (numbers) directly as nodes.
2. When you see an **operator**:
   - Pop the **right operand**.
   - Pop the **left operand**.
   - Create a new operator node with these as children.
   - Push the new node back.

At the end, the stack will contain **one node**: the root of the expression tree.

---

## 🧩 Your Task in `tree.c`

Students only need to implement **two functions**:

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

## 🖨️ Printing, Evaluating, and Freeing the Tree

These are already implemented:
- `printInfix(Node *root, FILE *out);`
- `int evaluate(Node *root);`
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
- You only edit `tree.c`, under the **"write your code here"** markers.  
- The rest of the code (stack, printing, evaluation, freeing) is already done for you.

---
