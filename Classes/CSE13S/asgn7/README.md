Assignment 7: Lempel-Ziv Compression
-------------------
DESCRIPTION

Storing large amounts of data has always been a problem for Computer Scientists. IBM’s report on Big Data in 2011 states that “we create 2.5 quintillion bytes of data” every day and that number has only increased since then. As such, it is imperative that as up-and-coming Computer Scientists we learn methods of compressing data in order to more quickly transfer and easily store bits, which results in freeing up storage and increasing network capacity. There are two categories of data compression algorithms: lossy and lossless. The former loses some data but retains most of it, and the latter doesn’t lose any. In this lab, we aim to implement some of these algorithms in C ourselves.

-------------------
FILES

- DESIGN.pdf

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- Makefile

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- decode.c

Contains main() for decode program

- encode.c

Contains main() for Encode program

- trie.{c, h}

Source and header file for Trie ADT

- word.{c, h}

Source and header file for Word ADT

- io.{c, h}

Source and header file for I/O ADT

- endian.h

Header file for Endianness module

- code.h

Header file containing macros for Reserved Codes

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn7 repository
3. Enter "make" into terminal
4. Type ./encode followed by any of the following options to edit program
-i [filename] : specifies file to read from, default stdin
-o [filename] : specifies file to write to, default stdout
-v : Enables statistics
-h : Help menu
5. Enter words into stdin if you didn’t specify a file to read from
6. Tap ctrl + d to exit (ctrl + d twice if you didn’t make a new line)
7. Type ./decode followed by any of the following options to edit program
-i [filename] : specifies file to read from, default stdin
-o [filename] : specifies file to write to, default stdout
-v : Enables statistics
-h : Help menu
8. Watch the file decompress and output either to stdout or to a file you specify
9. Enter “make clean” to clean up the executable

-------------------
SCAN-BUILD ERRORS
1.  Error when appending syms within word.c due to the result of calloc being converted into a different type. This error can be disregarded because we must cast it in order to make it an array of syms (which is of type uint8_t *)
