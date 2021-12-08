Assignment 5: Putting Your Affairs in Order
-------------------
DESCRIPTION

Computer scientists often have to put items into a sorted order when dealing with data. Consequently, there are a lot of different ways to do these sorts. Some of these methods include bubble sort, heap sort, quick sort, and shell sort. In this lab, we seek to implement these library functions/sorts in C and identify the strengths and weaknesses of each method.

-------------------
FILES

- DESIGN.pdf

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- README.md

This is the file you’re reading right now. It contains information about building, running, and options of the program.

- WRITEUP.pdf

Identifies respective time complexity, what I learned, how I experimented, graphs, and analysis of these graphs

- Makefile

This file allows the user to run commands such as "make", "make clean", “make format”, and "make all.”

- bubble/shell/quick/heap.c

Contains implementations of the sorts.

- bubble/shell/quick/heap.h

Contains prototypes of the sorts.

- sorting.c

Contains main() and others things needed to complete the assignment.

- comparisons.h

Included compares and moves to return to sorting.c

- stack/set.{c,h}

Includes the prototypes and implementation of the stack/set files.

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn5 repository
3. Enter "make" into terminal
4. Type ./sorting followed by any of the following options to edit program
-a: run through all sorts
-b: run through bubble sort
-s: run through shell sort
-q: run through quick sort
-h: run through heap sort
-r: set random seed
-n: set size of array
-p: set number to be printed
5. Wait for the program to compile
6. Enter “make clean” to remove files



