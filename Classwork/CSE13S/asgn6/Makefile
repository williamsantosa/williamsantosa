CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: 
	$(CC) $(CFLAGS) -o banhammer *.c -lm 

clean:
	rm -f banhammer node ll hash bv bf

format:
	clang-format -i -style=file *.[ch]

scan: clean
	scan-build make

valgrind: all
	valgrind -s --leak-check=full ./banhammer -i checkingerror

node:
	$(CC) $(CFLAGS) -o node node.c -lm

ll:
	$(CC) $(CFLAGS) -o ll ll.c node.c -lm

hash:
	$(CC) $(CFLAGS) -o hash hash.c ll.c node.c speck.c -lm

bv:
	$(CC) $(CFLAGS) -o bv bv.c -lm

bf:
	$(CC) $(CFLAGS) -o bf bf.c bv.c hash.c ll.c node.c speck.c -lm
