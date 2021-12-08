#include "word.h"

#include "code.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    if (w) {
        w->len = len;
        w->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
        if (w->syms) {
            for (uint32_t i = 0; i < len; i++) {
                w->syms[i] = syms[i];
            }
        }
    }
    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *rv = (Word *) malloc(sizeof(Word));
    uint8_t *new_syms = (uint8_t *) calloc(w->len + 1, sizeof(Word));
    rv->len = w->len + 1;
    for (uint32_t i = 0; i < (rv->len) - 1; i++) {
        new_syms[i] = w->syms[i];
    }
    new_syms[w->len] = sym;
    rv->syms = new_syms;
    return rv;
}

void word_delete(Word *w) {
    if (w != NULL) {
        free(w->syms);
        w->syms = NULL;
        free(w);
        w = NULL;
    }
    return;
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    if (wt) {
        wt[EMPTY_CODE] = word_create(NULL, 0);
    }
    return wt;
}

void wt_reset(WordTable *wt) {
    for (int i = START_CODE; i < MAX_CODE; i++) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
    return;
}

void wt_delete(WordTable *wt) {
    for (int i = EMPTY_CODE; i < MAX_CODE; i++) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
    free(wt);
    return;
}

// Helper function to print out contents of word
void word_print(Word *w) {
    for (uint32_t i = 0; i < (w->len); i++) {
        printf("%" PRIu8 ", ", w->syms[i]);
    }
    printf("\n");
    return;
}
