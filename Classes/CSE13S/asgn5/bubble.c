#include "bubble.h"

#include "comparisons.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t bubble_moves = 0;
uint64_t bubble_comparisons = 0;

uint64_t get_bubble_moves(void) {
    return bubble_moves;
}

uint64_t get_bubble_comparisons(void) {
    return bubble_comparisons;
}

void bubble_sort(uint32_t *A, uint32_t n) { // Pointer of the array, size of array
    bool swapped = true;
    uint32_t size = n;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i <= size; i++) {
            bubble_comparisons++;
            if (A[i] < A[i - 1]) {
                uint32_t temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                swapped = true;
                bubble_moves += 3;
            }
        }
        size -= 1;
    }
    return;
}
