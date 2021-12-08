#include "shell.h"

#include "gaps.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t shell_moves = 0;
uint64_t shell_comparisons = 0;

uint64_t get_shell_moves(void) {
    return shell_moves;
}

uint64_t get_shell_comparisons(void) {
    return shell_comparisons;
}

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t c = 0; c < GAPS; c++) {
        uint32_t gap = gaps[c];
        for (uint32_t i = gap; i < n; i++) {
            shell_comparisons++;
            uint32_t j = i;
            uint32_t temp = A[i];
            while ((j >= gap) && (temp < A[j - gap])) {
                A[j] = A[j - gap];
                A[j - gap] = temp;
                j -= gap;
                shell_moves += 3;
            }
            A[j] = temp;
        }
    }
}
