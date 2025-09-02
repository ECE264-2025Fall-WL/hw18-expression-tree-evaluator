[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/eD96uqUN)
# Who Gets the Cake

## Learning Goals
1. Dynamic Memory (malloc)
2. Algorithm design

## Problem Statement
Imagine that there are `n` people, represented by `n` elements in an array. In C, an array's index starts from 0 (i.e., indexes 0, 1, 2, ..., n-1). For clarity in the example, we will refer to these people by their conceptual number from 1 to `n` (so person `P` is at array index `P-1`).

These `n` people form a circle and decide who gets a piece of cake by playing a game:

1.  They choose an integer `k` greater than one. Both `n` and `k` must be greater than one. It is possible that `k` is greater than `n`.
2.  **Initial Round:** Counting starts from the first person (index 0 / person 1) and proceeds **forward**.
3.  They count `1, 2, 3, ..., k`. The `k`-th person is eliminated.
4.  After each elimination, the counting direction **reverses** for the next round.
    *   If the previous round was counting forward, the next round counts backward.
    *   If the previous round was counting backward, the next round counts forward.
5.  **Restarting the Count:** For the new round, counting `1, 2, 3, ...` begins from the first *available* person encountered immediately after the previously eliminated person, *in the new counting direction*.
    *   To find this starting person: Take the index of the person just eliminated. Advance one step in the *new* direction. Then, keep advancing in the *new* direction, skipping any already eliminated people, until you find the first non-eliminated person. This person becomes the starting point (`1`) for the next count of `k`.
6.  **Skipping Eliminated People:** If an element has already been eliminated, this element is skipped during counting. The count `1, 2, 3, ...` only increments for *available* people.
7.  **Wrapping Around:** When reaching the end of the array (or beginning), the counting wraps around to the other end of the array.
8.  The process continues until only one person is left. This person gets the cake.

## Example

Here's an example when `n` is 6 and `k` is 3. We will output the conceptual person number (1-6) that is eliminated.

**Initial state:**
People: `[1, 2, 3, 4, 5, 6]` (array indices `0, 1, 2, 3, 4, 5`)
Direction: **FORWARD**

**Round 1: Eliminate person 3 (index 2)**
*   Counting forward from person 1 (index 0):
    *   Person 1 (count 1)
    *   Person 2 (count 2)
    *   Person 3 (count 3) -> **Eliminate person 3**.
*   Output: `3`
*   Remaining people (conceptually): `[1, 2, X, 4, 5, 6]`
*   Last eliminated index: 2
*   Next round direction: **BACKWARD**

**Find starting person for Round 2 (Backward):**
*   Start from (last eliminated index - 1 + n) % n = (2 - 1 + 6) % 6 = 1 (Person 2).
*   Person 2 (index 1) is not eliminated. So, count `1` starts from Person 2 (index 1).

**Round 2: Eliminate person 6 (index 5)**
*   Counting backward from Person 2 (index 1):
    *   Person 2 (count 1)
    *   Person 1 (count 2)
    *   Person 6 (count 3) -> **Eliminate person 6**.
*   Output: `6`
*   Remaining people (conceptually): `[1, 2, X, 4, 5, X]`
*   Last eliminated index: 5
*   Next round direction: **FORWARD**

**Find starting person for Round 3 (Forward):**
*   Start from (last eliminated index + 1) % n = (5 + 1) % 6 = 0 (Person 1).
*   Person 1 (index 0) is not eliminated. So, count `1` starts from Person 1 (index 0).

**Round 3: Eliminate person 4 (index 3)**
*   Counting forward from Person 1 (index 0):
    *   Person 1 (count 1)
    *   Person 2 (count 2)
    *   (Person 3 is X, skip)
    *   Person 4 (count 3) -> **Eliminate person 4**.
*   Output: `4`
*   Remaining people (conceptually): `[1, 2, X, X, 5, X]`
*   Last eliminated index: 3
*   Next round direction: **BACKWARD**

**Find starting person for Round 4 (Backward):**
*   Start from (last eliminated index - 1 + n) % n = (3 - 1 + 6) % 6 = 2 (Person 3).
*   Person 3 (index 2) is X (eliminated), so skip.
*   Next backward: (2 - 1 + 6) % 6 = 1 (Person 2).
*   Person 2 (index 1) is not eliminated. So, count `1` starts from Person 2 (index 1).

**Round 4: Eliminate person 5 (index 4)**
*   Counting backward from Person 2 (index 1):
    *   Person 2 (count 1)
    *   Person 1 (count 2)
    *   (Person 6 is X, skip)
    *   Person 5 (count 3) -> **Eliminate person 5**.
*   Output: `5`
*   Remaining people (conceptually): `[1, 2, X, X, X, X]`
*   Last eliminated index: 4
*   Next round direction: **FORWARD**

**Find starting person for Round 5 (Forward):**
*   Start from (last eliminated index + 1) % n = (4 + 1) % 6 = 5 (Person 6).
*   Person 6 (index 5) is X (eliminated), so skip.
*   Next forward: (5 + 1) % 6 = 0 (Person 1).
*   Person 1 (index 0) is not eliminated. So, count `1` starts from Person 1 (index 0).

**Round 5: Eliminate person 1 (index 0)**
*   Counting forward from Person 1 (index 0):
    *   Person 1 (count 1)
    *   Person 2 (count 2)
    *   (Persons 3,4,5,6 are X, skip)
    *   (Wrap around)
    *   Person 1 (count 3) -> **Eliminate person 1**.
*   Output: `1`
*   Remaining people (conceptually): `[X, 2, X, X, X, X]`
*   Last eliminated index: 0
*   Next round direction: **BACKWARD**

**Final Remaining Person:**
Only Person 2 (index 1) is left.
*   Output: `2`

The full output for `n=6, k=3` is:
```
3
6
4
5
1
2
```

## Constraints
```
n <= 10000
k <= 10000
```

## What Do You Need to Do
Write the `eliminate` function which simulates the game as described above. Your function should print the **conceptual person number** (1 to `n`) of each eliminated element on a new line, and finally print the conceptual person number of the last remaining element.

## Submission
Push your completed code to GitHub and submit the repository to Gradescope.
Alternatively, submit your `eliminate.c` file to Gradescope.

## Additional Reading
This problem is inspired by the "Josephus problem". This assignment presents a variation of the classic problem where the elimination order reverses, making the direct mathematical solution more complex. If you are interested in the mathematical properties of the standard Josephus problem, you might find information in books like "Concrete Mathematics" by Ronald L. Graham, Donald E. Knuth, and Oren Patashnik.

## History
The Josephus problem is a famous mathematical puzzle, historically attributed to Flavius Josephus. According to the story, Josephus and 40 soldiers were trapped by Roman soldiers. They chose suicide over capture, forming a circle and deciding an order of elimination. Josephus supposedly calculated where to stand to be the last person remaining, allowing him to survive and surrender.
