#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "i:o:vh"

int infile = STDIN_FILENO;
int outfile = STDOUT_FILENO;
bool v = false;

uint16_t bit_length(uint16_t bits) {
    uint16_t rv = 0;
    while (bits) {
        rv++;
        bits >>= 1;
    }
    return rv;
}

int main(int argc, char **argv) {
    // Step One & Three
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile < 0) {
                fprintf(stderr, "Failed to open %s.\n", optarg);
                exit(1);
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile < 0) {
                fprintf(stderr, "Failed to open %s.\n", optarg);
                exit(1);
            }
            break;
        case 'v': v = true; break;
        case 'h':
        default:
            printf("SYNOPSIS\n   Decompresses files with the LZ78 decompression algorithm.\n   "
                   "Used with files compressed with the corresponding encoder.\n\nUSAGE\n   "
                   "./decode [-vh] [-i input] [-o output]\n\nOPTIONS\n   -v         Display "
                   "decompression statistics\n   -i input   Specify input to decompress (default: "
                   "stdin)\n   -o output  Specify output of decompressed input (default: stdout)\n "
                   "  -h         Display program usage\n");
            exit(0);
        }
    }

    // Step Two
    struct stat sb;
    fstat(infile, &sb);
    FileHeader header = { 0, 0 };
    read_header(infile, &header);
    if (header.magic != MAGIC) {
        fprintf(stderr, "Bad magic number.\n");
        exit(0);
    }
    fchmod(outfile, header.protection);

    // Step Four & Five
    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;

    // Step Six
    while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code)) == true) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code = next_code + 1;
        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
    }

    // Step Seven
    flush_words(outfile);

    // File Statistics
    if (v) {
        printf("Compressed file size: %" PRIu64 " bytes\n", total_bits / 8);
        printf("Uncompressed file size: %" PRIu64 " bytes\n", total_syms);
        printf("Space saving: %2.2f%%\n",
            (double) 100 * ((double) 1 - ((double) (total_bits / 8) / (double) (total_syms))));
    }

    // Step Eight
    close(infile);
    close(outfile);

    // Delete and Free Memory
    wt_delete(table);
    return 0;
}
