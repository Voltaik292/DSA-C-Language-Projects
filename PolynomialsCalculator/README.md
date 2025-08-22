# Polynomial Operations using Linked List & Stack (C)

This project implements a **Polynomial Abstract Data Type (ADT)** using **Stack of Linked Lists** in C Language.  
The application supports **Addition, Subtraction, and Multiplication** of polynomials.
All the operations are stack based operations.

## Menu
1. Load the polynomials file. 
2. Print the polynomials.
3. Add the polynomials.
4. Subtract the polynomials.  
5. Multiply the polynomials.  
6. Print the results to the screen.  
7. Print the results to the file. 
8. Exit.

## Example Input File
```
3x^5-2x^3+3x^2+4
-x^2-3x^4
8x^2-9
```

## How stack operations happen
```
Stack Addition Simulation Example:
Suppose you have 4 polynomials D, C, B, A
Initial stack (top → bottom): D, C, B, A
After 1st ADD: D+C, B, A
After 2nd ADD: (D+C)+B, A
After 3rd ADD: ((D+C)+B)+A
# Result will be dsiplayed to results.txt outputfile
```
