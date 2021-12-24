Assignment 3: The Game of Life
-------------------
DESCRIPTION

In this lab, we implement Conway’s “Game of Life” in C. To accomplish that, we implement different functions specified within the universe.h file within universe.c as well as create a life.c file which allows us to run it as an executable binary. The program will accept a variety of command line options to alter the “Game of Life.”

-------------------
FILES

- DESIGN.pdf

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- README.md

This is the file you’re reading right now. It contains information about building, running, and options of the program.

- life.c

This file allows for input and outputs the Game of Life.

- universe.h

This file includes the prototypes of the functions we need to implement as well as struct Universe.

- universe.c

This file includes my implementations for the functions we need to implement as well as struct Universe’s implementations.

- Makefile

This file allows the user to run commands such as "make", "make clean", “make format”, and "make all.”

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn3 repository
3. Enter "make" into terminal
4. Type ./life followed by any of the following options to edit program
-t: set game universe to be toroidal
-s: silence ncurses
-n <generations>: specify number of generations that the universe goes through
-i <input>: specify input file
-o <output>: specify output file
5. Wait for the program to compile
6. Enter “make clean” to remove files


