Assignment 4: Hamming Codes
-------------------
DESCRIPTION

A Hamming Code is a simple encoding and decoding technique that allows receivers and senders to transmit extra bits of data in order to detect and correct these errors. In this lab, we implement our own Hamming Code within C using the following files.

-------------------
FILES

- generator.c

Contains my implementation of the Hamming Code generator.

- decoder.c

Contains my implementation of the Hamming Code decoder.

- bm.h

Contains the BitMatrix ADT interface

- bm.c

Contains my implementation of the BitMatrix ADT interface

- hamming.h

File provided in resources repository, contains the Hamming Code module

- hamming.c

Contains my implementation of the Hamming Code module

- error.c

File provided in the resources repository, allows us to check errors made.

- Makefile

Runs program (All, gen, dec, err, clean, format)

- README.md

This is the file you’re reading right now. It contains information about building, running, and options of the program.

- DESIGN.pdf

Describes purpose, covers the layout, clear description of program parts, pseudo code, and contains the pre lab questions.

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn4 repository
3. Enter "make" into terminal
4. Type ./gen followed by the following options to output a code
-i <input>: specify input file
-o <output>: specify output file
5. Type ./dec followed by the following options to output the decoded code
-i <input>: specify input file
-o <output>: specify output file
6. Enter “make clean” to remove files


