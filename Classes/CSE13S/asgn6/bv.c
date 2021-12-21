#include "bv.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Entire thing is super similar to BitMatrix

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    bv->length = length;
    bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = (1 << (i % 8));
    bv->vector[i / 8] = byte | mask;
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = ~(1 << (i % 8));
    bv->vector[i / 8] = byte & mask;
    return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t byte = bv->vector[i / 8];
    uint8_t mask = (1 << (i % 8));
    byte = byte & mask;
    byte = byte >> (i % 8);
    return byte;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < (bv->length); i++) {
        printf("%" PRIu8, bv_get_bit(bv, i));
    }
    printf("\n");
    return;
}
