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

uint16_t bit_length(uint16_t number) {
    uint16_t rv = 0;
    if (number == 0) {
        return 1;
    }
    while (number) {
        rv++;
        number >>= 1;
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
            printf("SYNOPSIS\n   Compresses files using the LZ78 compression algorithm.\n   "
                   "Compressed files are decompressed with the corresponding decoder.\n\nUSAGE\n   "
                   "./encode [-vh] [-i input] [-o output]\n\nOPTIONS\n   -v         Display "
                   "compression statistics\n   -i input   Specify input to compress (default: "
                   "stdin)\n   -o output  Specify output of compressed input (default: stdout)\n   "
                   "-h         Display program help and usage\n");
            exit(0);
        }
    }
    // Step Two
    struct stat sb;
    fstat(infile, &sb);
    FileHeader header = { 0, 0 };
    header.magic = MAGIC;
    header.protection = sb.st_mode;
    fchmod(outfile, header.protection);

    // Step Four
    write_header(outfile, &header);

    // Step Five
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    uint8_t curr_sym = 0;

    // Step Six
    uint16_t next_code = START_CODE;

    // Step Seven
    uint8_t prev_sym = 0;
    TrieNode *prev_node = NULL;

    // Step Eight
    while (read_sym(infile, &curr_sym) == true) {
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }

    // Step Nine
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }

    // Step Ten
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));

    // Step Eleven
    flush_pairs(outfile);

    // File Statistics
    if (v) {
        printf("Compressed file size: %" PRIu64 " bytes\n", total_bits / 8);
        printf("Uncompressed file size: %" PRIu64 " bytes\n", total_syms);
        printf("Space saving: %2.2f%%\n",
            (double) 100 * ((double) 1 - ((double) (total_bits / 8) / (double) (total_syms))));
    }

    // Step Twelve
    close(infile);
    close(outfile);

    // Delete and Free Memory
    trie_delete(root);
    return 0;
}
