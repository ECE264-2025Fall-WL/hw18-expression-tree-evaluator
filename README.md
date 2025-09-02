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

### Expression Tree
An **expression tree** is a binary tree where:
- **Leaves** = operands (numbers/variables).
- **Internal nodes** = operators.

Example for `(3 + 4) * 5`:

```
       *
      / \
     +   5
    / \
   3   4
```

- **Inorder traversal (L-root-R)** → `(3 + 4) * 5`  
- **Preorder traversal (root-L-R)** → `* + 3 4 5`  
- **Postorder traversal (L-R-root)** → `3 4 + 5 *`

---

## 🧩 Part 1: Building the Expression Tree

### Function
```c
Node* buildExpressionTree(char *tokens[], int count);
```

### Algorithm
1. Initialize an empty **stack** of nodes.
2. Scan each token:
   - If **operand** → create node, push onto stack.
   - If **operator** → pop two nodes (right, then left), make them children of a new operator node, push result.
3. After processing all tokens, one node remains = **root**.

### Example
Postfix: `3 4 + 5 *`

Steps:
1. Push `3`  
2. Push `4`  
3. See `+` → pop `4, 3` → create `+` → push  
4. Push `5`  
5. See `*` → pop `5, +` → create `*` → push  

Result: Root is `*`.

---

## 🖨️ Part 2: Printing the Expression

### Function
```c
void printInfix(Node *root, FILE *out);
```

### Algorithm
- Perform an **inorder traversal**:
  1. Print left subtree.
  2. Print operator.
  3. Print right subtree.
- Add **parentheses** around sub-expressions to preserve order.

### Example
Tree for `3 4 + 5 *` prints as:
```
(3 + 4) * 5
```

---

## 🧮 Part 3: Evaluating the Expression

### Function
```c
int evaluate(Node *root);
```

### Algorithm
- Recursive **postorder style**:
  - If leaf: return value.
  - If operator: evaluate left and right, then apply operator.

### Example
For `(3 + 4) * 5`:
- Left: `3+4=7`
- Right: `5`
- Multiply: `7*5=35`

Output:
```
(3 + 4) * 5 = 35
```

---

## 🧹 Part 4: Freeing Memory

### Function
```c
void freeTree(Node *root);
```

### Algorithm
- Use **postorder traversal**:
  - Free left.
  - Free right.
  - Free current node.

Prevents memory leaks when running multiple tests.

---

## 🖥️ Main Program

`main.c` is provided and does the following:

1. Reads filenames from command-line args:
   ```bash
   ./expr input.txt output.txt
   ```
2. Reads tokens (postfix expression) from `input.txt`.
3. Builds the tree with `buildExpressionTree()`.
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
stack.c
tree.c
```

Zip and upload:
```bash
zip hw18.zip stack.c tree.c
```

Do **not** submit `main.c` or the Makefile — they’re provided.

---

## ⚡ Key Takeaways

- Postfix → Expression Tree is **stack-based**.  
- Traversal order defines **notation** (infix, postfix, prefix).  
- **Recursion** simplifies both printing and evaluation.  
- Always **free memory** with `freeTree()`.  
- **Separate compilation** + Makefile help organize larger projects.  

---

## 📝 Worked Example Trace

Expression:  
```
5 6 2 + * 12 4 / -
```

1. Push `5`.  
2. Push `6`.  
3. Push `2`.  
4. See `+` → pop `2, 6` → make `(6 + 2)` node → push.  
5. See `*` → pop `(6+2), 5` → make `(5 * (6+2))` node → push.  
6. Push `12`.  
7. Push `4`.  
8. See `/` → pop `4, 12` → make `(12 / 4)` node → push.  
9. See `-` → pop `(12/4), (5*(6+2))` → make `((5*(6+2)) - (12/4))` node → push.  

Final tree:  
```
         -
       /   \
      *     /
     / \   / \
    5  + 12  4
      / \
     6   2
```

Evaluation:
- `(6+2)=8`  
- `5*8=40`  
- `12/4=3`  
- `40-3=37`  

✅ Output:
```
(5 * (6 + 2)) - (12 / 4) = 37
```
