#42-cpp-09

# Exercise 00: Bitcoin Exchange Project

## Overview
This project calculates the value of a given amount of Bitcoin using historical exchange rates stored in a CSV file.

## Requirements
- **Program Name:** `btc`
- **Input Format:** `"date | value"`
- **Valid Date Format:** `YYYY-MM-DD`
- **Valid Value Range:** `0 to 1000 BTC`
- **Database:** A CSV file containing historical exchange rates.

## Example Input (`input.txt`)
2011-01-03 | 2 <br/>
2012-01-11 | 1.5 <br/>
2005-05-20 | 3 <br/>

## Expected Output
2011-01-03 => 1 = 10.00 <br/>
2012-01-11 => 10.50 = 25 <br/>
Error: No date for 2005-05-33 <br/>
Error: not a positive number <br/>


# **Exercise 01: Reverse Polish Notation (RPN) - C++ Module 09**

## **Overview**
Reverse Polish Notation (RPN) is a mathematical notation where operators follow their operands. Unlike standard notation, **RPN does not require parentheses**, making it efficient for evaluating expressions.

This exercise focuses on implementing an RPN calculator using **C++ Standard Template Library (STL)**.

---

## **Objectives**
- Implement an RPN calculator in **C++**.
- Use **STL containers**, particularly `std::stack`, to process mathematical expressions.
- Validate and execute operations correctly.

---

## **What is Reverse Polish Notation?**
In RPN:
- **Operands** are pushed onto a stack.
- **Operators** pop the required number of operands and compute results.
- The final result remains on the stack.

Example:

Expression: "3 4 +" Standard notation: (3 + 4) RPN execution:

Input: "3 4 + 2 *"
Steps:
1. Push `3`
2. Push `4`
3. Apply `+`: `3 + 4 = 7`, push `7`
4. Push `2`
5. Apply `*`: `7 * 2 = 14`
Output: `14`

Key Takeaways

    Stacks are ideal for RPN evaluation.

    Expressions are processed left to right without needing parentheses.

    Error handling is crucial for invalid inputs.

# **Exercise 02: PmergeMe**

## **Overview**
PmergeMe is a project focused on implementing the **Merge-Insertion Sort algorithm**, a hybrid sorting method combining **merge sort** and **insertion sort** for optimized performance.

---

## **Objectives**
- Implement an efficient sorting algorithm using **C++ STL containers** (`vector`, `deque`).
- Compare the sorting performance between different data structures.
- Analyze and understand **time complexity** implications.

---

## **Algorithm Breakdown**
### **Merge-Insertion Sort Steps**
1. **Divide the Input** into small chunks.
2. **Sort Small Groups** using **Insertion Sort**.
3. **Merge Sorted Groups** efficiently using **Merge Sort**.

This approach balances **speed** (due to insertion sort for small sets) and **efficiency** (due to merge sort for larger merges).

---

## **Example C++ Implementation**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void mergeInsertionSort(vector<int>& arr) {
    if (arr.size() <= 1) return;
    
    // Split into pairs and sort using insertion
    for (size_t i = 1; i < arr.size(); i += 2)
        if (arr[i] < arr[i - 1]) swap(arr[i], arr[i - 1]);

    // Apply merge logic
    sort(arr.begin(), arr.end()); // Simplified for demonstration
}

int main() {
    vector<int> data = {9, 3, 7, 1, 6, 4};
    mergeInsertionSort(data);
    for (int num : data) cout << num << " ";
}
