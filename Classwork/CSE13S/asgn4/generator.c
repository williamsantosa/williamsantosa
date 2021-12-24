#include "bm.h"
#include "hamming.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:"

FILE *infile;
FILE *outfile;

uint8_t lower(uint8_t val) {
    return val & 0xF;
}

uint8_t upper(uint8_t val) {
    return val >> 4;
}

uint8_t pack(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    infile = stdin;
    outfile = stdout;
    // Step One
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                printf("%s: No such file or directory\n", optarg);
                stderr;
                exit(0);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (infile == NULL) {
                printf("%s: No such file or directory\n", optarg);
                stderr;
                exit(0);
            }
            break;
        }
    }

    // Step Two
    ham_init();

    // Step Three to Five
    int c = 0;
    uint8_t byte;
    while ((c = fgetc(infile)) != EOF) {
        byte = c;
        uint8_t low_output = 0;
        uint8_t up_output = 0;
        uint8_t *lowpoint = &low_output;
        uint8_t *uppoint = &up_output;
        uint8_t low_nibble = lower(byte);
        uint8_t up_nibble = upper(byte);
        uint8_t low_code = ham_encode(low_nibble, lowpoint);
        uint8_t up_code = ham_encode(up_nibble, uppoint);
        if (up_code || low_code) {
        }
        fputc(low_output, outfile);
        fputc(up_output, outfile);
    }

    // Step Six
    ham_destroy();

    // Step Seven
    fclose(infile);
    fclose(outfile);
    return 0;
}
