CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: 
	$(CC) $(CFLAGS) -o sorting *.c -lm 

clean:
	rm -f sorting

format:
	clang-format -i -style=file *.[ch]

scan: clean
	scan-build make

valgrind: all
	valgrind -s --leak-check=full ./sorting -i checkingerror
