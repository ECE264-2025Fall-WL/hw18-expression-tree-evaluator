# Expression Tree Evaluator

## 📚 Learning Goals

In this assignment, you will:

- **Understand expression notations**: infix, prefix, postfix (Reverse Polish Notation).
- **Build a binary expression tree** from a postfix expression.
- **Apply recursion** to traverse and evaluate binary trees.
- **Use dynamic memory** in C (`malloc`, `free`).
- **Separate compilation**: implement your code across multiple `.c` files with a header file.
- **Handle file I/O**: read tokens from an input file, write results to an output file.
- **Test and debug** with a Makefile and automated test cases.

---

## 🔑 Background Concepts

### Expression Notations
- **Infix**: operators between operands (e.g., `(3 + 4) * 5`).
- **Postfix (RPN)**: operators after operands (e.g., `3 4 + 5 *`).
- **Prefix**: operators before operands (e.g., `* + 3 4 5`).

Postfix is unambiguous and easy to evaluate with a stack, making it ideal for computer parsing.

### Expression Tree
- A **binary tree** where:
  - **Leaves** are operands (numbers/variables).
  - **Internal nodes** are operators (`+`, `-`, `*`, `/`).
- Traversals give you different notations:
  - **Inorder (L-root-R)** → Infix
  - **Preorder (root-L-R)** → Prefix
  - **Postorder (L-R-root)** → Postfix

Example for `(3 + 4) * 5`:

