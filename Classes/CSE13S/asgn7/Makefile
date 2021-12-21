CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: encode decode

encode:
	$(CC) $(CFLAGS) -o encode encode.c word.c trie.c io.c -lm

decode:
	$(CC) $(CFLAGS) -o decode decode.c word.c trie.c io.c -lm

clean:
	rm -f encode decode entropy trie word io

format:
	clang-format -i -style=file *.[ch]

scan: clean
	scan-build make

valgrind: all
	valgrind -s --leak-check=full ./encode ./decode -i checkingerror

trie:
	$(CC) $(CFLAGS) -o trie trie.c -lm

word:
	$(CC) $(CFLAGS) -o word word.c -lm

io:
	$(CC) $(CFLAGS) -o io io.c word.c -lm

entropy:
	$(CC) $(CFLAGS) -o entropy entropy.c -lm
