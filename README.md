#42-cpp-09

# Bitcoin Exchange Project

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

Input: "5 1 2 + 4 * + 3 -"
Result: `14`


