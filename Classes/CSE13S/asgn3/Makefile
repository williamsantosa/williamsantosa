all:
	clang -o life life.c universe.c -Wall -Wextra -Wpedantic -Werror -lncurses

clean:
	rm -f life

format:
	clang-format -i -style=file *.[ch]

scan: clean
	scan-build make

valgrind: all
	valgrind -s --leak-check=full ./life -i lists/Hertz-oscillator.txt -s -o out
