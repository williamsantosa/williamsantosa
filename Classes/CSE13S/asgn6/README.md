Assignment 6: The Great Firewall of Santa Cruz: Bloom Filters, Linked Lists and Hash Tables
-------------------
DESCRIPTION

Oddly, I, along with some other students, have been notified that we have been selected “through thoroughly democratic processes” to be the leader of the Glorious People’s Republic of Santa Cruz. As such, in an attempt to promote virtue, prevent vice, and preserve social cohesion, I have decided to filter internet content by implementing a variety of different methods using the files listed below.

-------------------
FILES

- DESIGN.pdf

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- Makefile

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- banhammer.c

This file includes my description of the program, the purpose, layout/structure, pseudocode, and alterations made to the doc.

- parser.{c, h}

Specifies the interface and implementation of Regex Parsing module.

- bv.{c, h}

Specifies the interface and implementation of Bit Vector module.

- bf.{c, h}

Specifies the interface and implementation of Bloom Filter module.

- node.{c, h}

Specifies the interface and implementation of Node module.

- ll.{c, h}

Specifies the interface and implementation of Linked List module.

- hash.{c, h}

Specifies the interface and implementation of Hash Table module.

- speck.{c, h}

Specifies the interface and implementation of SPECK cipher module.

-------------------
INSTRUCTIONS

1. Open up terminal
2. Enter ~/wsantosa/asgn6 repository
3. Enter "make" into terminal
4. Type ./banhammer followed by any of the following options to edit program
-h [size] : edits Hash table size
-f [size] : edits Bloom filter size
-m : Enables move-to-front
5. Enter words into stdint
6. Tap ctrl + d to exit (ctrl + d twice if you didn’t make a new line)
7. Review the mistakes you’ve made and determine if you need to leave a will before going to joycamp
8. Enter “make clean” to clean up the executable



