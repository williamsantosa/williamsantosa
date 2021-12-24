#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
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
    int bytesProcessed = 0;
    int uncorrectedErrors = 0;
    int correctedErrors = 0;
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

    // Step Three to Six
    int locode = 0;
    int hicode = 0;
    while (locode != EOF || hicode != EOF) {
        locode = fgetc(infile);
        hicode = fgetc(infile);
        if (locode == EOF || hicode == EOF) {
            goto exitloop;
        }
        uint8_t loc = locode;
        uint8_t hic = hicode;
        uint8_t low = 0;
        uint8_t up = 0;
        uint8_t *lowpoint = &low;
        uint8_t *uppoint = &up;
        ham_rc lonibble = ham_decode(loc, lowpoint);
        ham_rc upnibble = ham_decode(hic, uppoint);
        uint8_t byte = pack(up, low);
        fputc(byte, outfile);
        if (lonibble == -1) {
            uncorrectedErrors++;
        }
        if (upnibble == -1) {
            uncorrectedErrors++;
        }
        if (lonibble == 1) {
            correctedErrors++;
        }
        if (upnibble == 1) {
            correctedErrors++;
        }
        bytesProcessed += 2;
    }
exitloop:

    // Step Seven
    ham_destroy();

    // Step Eight
    fprintf(stderr, "Total bytes processed: %d\n", bytesProcessed);
    fprintf(stderr, "Uncorrected errors: %d\n", uncorrectedErrors);
    fprintf(stderr, "Corrected errors: %d\n", correctedErrors);
    fprintf(stderr, "Error rate: %1.6f\n", ((float) uncorrectedErrors) / ((float) bytesProcessed));

    // Step Nine
    fclose(infile);
    fclose(outfile);
    return 0;
}
