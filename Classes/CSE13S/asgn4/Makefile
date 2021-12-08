CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: gen dec err

gen:
	$(CC) $(CFLAGS) -o gen generator.c bm.c hamming.c

dec:
	$(CC) $(CFLAGS) -o dec decoder.c bm.c hamming.c

err:
	$(CC) $(CFLAGS) -o err error.c bm.c hamming.c

clean:
	rm -f gen dec err

format:
	clang-format -i -style=file *.[ch]

scan: clean
	scan-build make

valgrind: all
	valgrind -s --leak-check=full ./gen -i checkingerror
	valgrind -s --leak-check=full ./dec -i checkingerror
