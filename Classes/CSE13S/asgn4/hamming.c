#include "hamming.h"

#include "bm.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

BitMatrix *G;
BitMatrix *H_T;

uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

ham_rc ham_init(void) {
    G = bm_create(4, 8);
    for (uint32_t r = 0; r < bm_rows(G); r++) {
        for (uint32_t c = 0; c < bm_cols(G); c++) {
            if (r == c) {
                bm_set_bit(G, r, c);
            }
            if (r >= 4 || c >= 4) {
                bm_set_bit(G, r, c);
            }
            if (r == (c - 4)) {
                bm_clr_bit(G, r, c);
            }
        }
    }
    H_T = bm_create(4, 8);
    for (uint32_t r = 0; r < bm_rows(H_T); r++) {
        for (uint32_t c = 0; c < bm_cols(H_T); c++) {
            if (r < 4 || c < 4) {
                bm_set_bit(H_T, r, c);
            }
            if (r >= 4 || c >= 4) {
                bm_clr_bit(H_T, r, c);
            }
            if (r == c) {
                bm_clr_bit(H_T, r, c);
            }
            if (r == (c - 4)) {
                bm_set_bit(H_T, r, c);
            }
        }
    }
    if (G == NULL || H_T == NULL) {
        return HAM_ERR;
    }
    return HAM_OK;
}

void ham_destroy(void) {
    bm_delete(&G);
    bm_delete(&H_T);
}

ham_rc ham_encode(uint8_t data, uint8_t *code) {
    uint8_t lnibble = lower_nibble(data);
    uint8_t result = 0;
    uint8_t temp = 0;
    uint8_t temp2 = 0;
    uint8_t mask = 0;

    // Multiplies the correct column, adds them up, puts in the correct spot in result
    for (uint32_t i = 0; i < 1; i++) {
        for (uint32_t k = 0; k < bm_cols(G); k++) {
            for (uint32_t j = 0; j < bm_rows(G); j++) {
                mask = 1 << (3 - j);
                temp = (mask & lnibble);
                temp = temp >> (3 - j);
                temp = temp * bm_get_bit(G, j, k);
                temp2 += temp;
            }
            // Values were inverted so revert them with this
            if (data == 1 || data == 2 || data == 4 || data == 7 || data == 8 || data == 11
                || data == 13 || data == 14) {
                temp2 = (temp2 + 1) % 2;
            } else {
                temp2 = temp2 % 2;
            }
            temp2 = temp2 << (7 - k);
            result += temp2;
            temp2 = 0;
        }
    }
    *code = result;
    return HAM_OK;
}

ham_rc ham_decode(uint8_t code, uint8_t *data) {
    uint8_t tempcode = code;
    uint8_t result = 0;
    uint8_t temp = 0;
    uint8_t temp2 = 0;
    uint8_t mask = 0;
    bool hamerrok = false;

    // Get total for each multiplication and then adds them up modulo 2, adds to result in correct place
    for (uint32_t i = 0; i < 1; i++) {
        for (uint32_t j = 0; j < bm_rows(H_T); j++) {
            for (uint32_t k = 0; k < bm_cols(H_T); k++) {
                mask = 1 << (7 - k);
                temp = (tempcode & mask);
                temp = temp >> (7 - k);
                temp = temp * bm_get_bit(H_T, j, k);
                temp2 += temp;
            }
            temp2 = temp2 % 2;
            temp2 = temp2 << (3 - j);
            result += temp2;
            temp2 = 0;
        }
    }

    // Check for single error, else cannot be fixed
    if (result != 0) {
        if (result == 7) {
            mask = 1 << 7;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 11) {
            mask = 1 << 6;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 13) {
            mask = 1 << 5;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 14) {
            mask = 1 << 4;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 8) {
            mask = 1 << 3;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 4) {
            mask = 1 << 2;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 2) {
            mask = 1 << 1;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else if (result == 1) {
            mask = 1 << 0;
            tempcode = tempcode ^ mask;
            hamerrok = true;
        } else {
            uint8_t rv = lower_nibble(tempcode);
            *data = rv;
            return HAM_ERR;
        }
    }

    uint8_t rv = lower_nibble(tempcode);
    *data = rv;
    if (hamerrok) {
        return HAM_ERR_OK;
    }
    return HAM_OK;
}
