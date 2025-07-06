# Satellite Network Builder 🌐

This project implements a system for managing a satellite communication network using **binary trees** and **encoding/decoding traversal techniques**, as described in the second assignment of the Data Structures and Algorithms (SDA) course.

The satellite network is constructed based on the frequency of satellite transmissions, with lower-frequency nodes placed deeper in the tree. Several operations such as encoding/decoding messages, finding common ancestors, and structured tree output are implemented.

📁 **All logic and functionality are implemented in `main.c` and `structures.h`.**

## ✅ Features

- ✅ Binary tree construction using Min-Heap rules
- ✅ Custom satellite node types (with frequency + name)
- ✅ Encoding satellite names into binary traversal sequences
- ✅ Decoding binary traversal into satellite names
- ✅ Finding the Lowest Common Ancestor (LCA) of multiple satellites
- ❌ Bonus task (multiway tree extension & distance computation) **not implemented**

## 🧠 Task Summary

### 🌲 Task 1 – Tree Construction (30 points)
Builds a binary tree representing the satellite network using Min-Heap logic:
- Satellites with the lowest transmission frequency are combined via an intermediate node.
- The intermediate node name is the concatenation of its children's names.
- The tree is printed level by level.

✅ Implemented successfully using custom heap and tree structures.

### 🔁 Task 2 – Binary Path Decoding (20 points)
- Given binary sequences (`0` = left, `1` = right), traverses the binary tree to decode satellite names.

✅ Implemented using recursive binary tree traversal.

### 🛰️ Task 3 – Satellite Path Encoding (20 points)
- Given a list of satellite names, returns the binary encoding (path) to reach each from the root.

✅ Implemented using depth-first traversal + backtracking.

### 👨‍🚀 Task 4 – Lowest Common Ancestor (25 points)
- Finds the closest common ancestor (by name) of a given list of satellites.

✅ Implemented using standard LCA logic in trees.

## 📁 Project Structure

- `main.c`: Solution implementation
- `structures.h`: Data structures and their corresponding basic functions
- `Makefile`: Contains `build` and `clean` rules
- `README.md`: This file
- `README`: Original README file used for the assignment

## ⚙️ Build & Run

Compile:
```bash
make build
```

Run:
```bash
./tema2 -c1 input.txt output.txt   # Task 1
./tema2 -c2 input.txt output.txt   # Task 2
./tema2 -c3 input.txt output.txt   # Task 3
./tema2 -c4 input.txt output.txt   # Task 4
```

Clean:
```bash
make clean
```

## 📌 Notes

- Implemented all required data structures: `TreeNode`, `MinHeap`, and custom satellite types
- Input parsing and output are fully compliant with the expected format
- All memory allocations are freed correctly
- 🧼 Clean coding style, no compiler warnings
