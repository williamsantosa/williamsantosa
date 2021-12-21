#include "io.h"

#include "code.h"
#include "endian.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t sbuf[BLOCK]; // Buffer for syms
static uint8_t pbuf[BLOCK]; // Buffer for read/write pair
static int symbol_index = 0;
static int bit_index = 0;
static int end = -1;
uint64_t total_syms = 0; // To count the symbols processed.
uint64_t total_bits = 0; // To count the bits processed.

// Set/Clr Helper Functions

void set_bit(uint8_t *buf, uint32_t i) {
    uint8_t byte = buf[i / 8];
    uint8_t mask = (1 << (i % 8));
    buf[i / 8] = byte | mask;
    return;
}

void clr_bit(uint8_t *buf, uint32_t i) {
    uint8_t byte = buf[i / 8];
    uint8_t mask = ~(1 << (i % 8));
    buf[i / 8] = byte & mask;
    return;
}

void set_bit8(uint8_t *code, uint32_t i) {
    uint8_t byte = *code;
    uint8_t mask = (1 << (i % 8));
    *code = byte | mask;
    return;
}

void clr_bit8(uint8_t *code, uint32_t i) {
    uint8_t byte = *code;
    uint8_t mask = ~(1 << (i % 8));
    *code = byte & mask;
    return;
}

void set_bit16(uint16_t *code, uint32_t i) {
    uint16_t byte = *code;
    uint16_t mask = (1 << (i % 16));
    *code = byte | mask;
    return;
}

void clr_bit16(uint16_t *code, uint32_t i) {
    uint16_t byte = *code;
    uint16_t mask = ~(1 << (i % 16));
    *code = byte & mask;
    return;
}

// Get Bit Helper Functions

uint8_t get_bit8(uint8_t sym, uint32_t i) {
    uint8_t byte = sym;
    uint8_t mask = (1 << (i % 8));
    byte = byte & mask;
    byte = byte >> (i % 8);
    return byte;
}

uint16_t get_bit16(uint16_t code, uint32_t i) {
    uint16_t byte = code;
    uint16_t mask = (1 << (i % 16));
    byte = byte & mask;
    byte = byte >> (i % 16);
    return byte;
}

uint8_t get_bit(uint8_t *buf, uint32_t i) {
    uint8_t byte = buf[i / 8];
    uint8_t mask = (1 << (i % 8));
    byte = byte & mask;
    byte = byte >> (i % 8);
    return byte;
}

// Bytes Helper Function

uint32_t bytes(uint32_t bit_index) {
    uint32_t rv = 0;
    if (bit_index % 8 == 0) {
        rv = bit_index / 8;
    } else { // Needed an extra, because division rounds down in C
        rv = (bit_index / 8) + 1;
    }
    return rv;
}

// Start of stuff

int read_bytes(int infile, uint8_t *buf, int to_read) {
    if (to_read == 0) {
        return 0;
    }
    int total_to_read = to_read;
    int bytes = 0; // Bytes read
    int total = 0; // Total bytes read
    while ((bytes = read(infile, buf + total, total_to_read)) > 0) {
        if (bytes == EOF) {
            goto e;
        }
        if (bytes == -1) {
            fprintf(stderr, "Error when reading bytes.");
            exit(1);
        }
        total += bytes;
        total_to_read -= bytes;
        // buf += bytes; // Shift buff by amount read
    }
e:
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int total_to_write = to_write;
    int bytes = 0; // Bytes read
    int total = 0; // Total bytes read
    while ((bytes = write(outfile, buf + total, total_to_write)) > 0) {
        if (bytes == EOF) {
            goto e;
        }
        if (bytes == -1) {
            fprintf(stderr, "Error when reading bytes.");
            exit(1);
        }
        total += bytes;
        total_to_write -= bytes;
        // buf += bytes; // Shift buff by amount read
    }
e:
    return total;
}

void read_header(int infile, FileHeader *header) {
    total_bits += 8 * sizeof(header);
    // Check number of read_bytes and error checks later
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    return;
}

void write_header(int outfile, FileHeader *header) {
    total_bits += 8 * sizeof(header);
    // Check number of write_bytes and error checks later
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
    return;
}

bool read_sym(int infile, uint8_t *sym) {
    // Need to figure out when to put in return false (when no more to be read, maybe read_bytes < BLOCK)
    int bytes = 0;
    if (symbol_index == 0) {
        bytes = read_bytes(infile, sbuf, BLOCK);
        if (bytes < BLOCK) {
            end = bytes + 1;
        }
    }
    *sym = sbuf[symbol_index];

    symbol_index += 1;
    if (symbol_index == BLOCK) {
        symbol_index = 0;
    }
    if (symbol_index == end) {
        return false;
    }
    total_syms++;
    return true;
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    if (big_endian()) {
        code = swap16(code);
    }
    // For Code
    for (int i = 0; i < bitlen; i++) {
        if (get_bit16(code, i) == 1) {
            set_bit(pbuf, bit_index);
        } else { // if bit is a zero
            clr_bit(pbuf, bit_index);
        }
        bit_index++;
        if (bit_index == BLOCK * 8) {
            flush_pairs(outfile);
        }
    }
    // For Sym
    for (int i = 0; i < 8; i++) {
        if (get_bit8(sym, i)) {
            set_bit(pbuf, bit_index);
        } else {
            clr_bit(pbuf, bit_index);
        }
        bit_index++;
        if (bit_index == BLOCK * 8) {
            flush_pairs(outfile);
        }
    }
    total_bits += bitlen + 8;
    return;
}

void flush_pairs(int outfile) {
    if (bit_index > 0) {
        write_bytes(outfile, pbuf, bytes(bit_index));
        bit_index = 0;
        for (int i = 0; i < BLOCK; i++) {
            pbuf[i] = 0;
        }
    }
    return;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    // For Code
    uint16_t tempcode = 0;
    for (int i = 0; i < bitlen; i++) {
        if (bit_index == 0) { // Empty buffer
            read_bytes(infile, pbuf, BLOCK);
        }
        if (get_bit(pbuf, bit_index) == 1) {
            set_bit16(&tempcode, i);
        } else {
            clr_bit16(&tempcode, i);
        }
        bit_index++;
        if (bit_index == BLOCK * 8) {
            bit_index = 0;
        }
    }
    *code = tempcode;
    // For Sym
    uint8_t tempsym = 0;
    for (int i = 0; i < 8; i++) {
        if (bit_index == 0) { // Empty buffer
            read_bytes(infile, pbuf, BLOCK);
        }
        if (get_bit(pbuf, bit_index) == 1) {
            set_bit8(&tempsym, i);
        } else {
            clr_bit8(&tempsym, i);
        }
        bit_index++;
        if (bit_index == BLOCK * 8) {
            bit_index = 0;
        }
    }
    *sym = tempsym;
    // End
    if (big_endian()) {
        *code = swap16(*code);
    }
    if (tempcode == STOP_CODE) {
        return false; // No more
    } else {
        return true; // Still some
    }
    total_bits += bitlen + 8;
}

void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < (w->len); i++) {
        sbuf[symbol_index] = (w->syms[i]);
        symbol_index++;
    }
    if (symbol_index == BLOCK * 8) {
        flush_words(outfile);
    }
    total_syms++;
    return;
}

void flush_words(int outfile) {
    if (symbol_index > 0) {
        write_bytes(outfile, sbuf, symbol_index);
        symbol_index = 0;
        for (int i = 0; i < BLOCK; i++) {
            sbuf[i] = 0;
        }
    }
    return;
}
