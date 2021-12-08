Assignment 2: A Small Numerical Library
-------------------
DESCRIPTION

In this lab, we implement a couple different functions from the math.h library ourselves and compare both of them to gain a better understanding of how to use these functions and to deepen our comprehension on computer computations.

-------------------
FILES

- DESIGN.pdf

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- mathlib-test.c

This file allows for input and prints out the test cases.

- mathlib.h

This file includes the prototypes of the functinos we need to implement.

- mathlib.c

This file includes my implementations for Sin, Cos, tan, Exp, and Log.

- Makefile

This file allows the usr to run commands such as "make", "make clean", and "make all"

- WRITEUP.pdf

This file includes graphs and analyzes the differences in output of my implementations vs. output from math.h.

-------------------
BUILD ERRORS
1. Only one build error where it states that some values are "garbage values" This is disregardable as it doesn't matter if some values are set, since only the needed ones specified are printed out.

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn2 repository
3. Enter "make" into terminal
4. Run the program by entering "./mathlib-test" along with any other command line wanted 
   (-a for all, 
    -s for Sin, 
    -c for Cos, 
    -t for Tan, 
    -e for Exp, 
    -l for Log)
5. Wait for the executable to compile
6. Enter "make clean" to clean up files
