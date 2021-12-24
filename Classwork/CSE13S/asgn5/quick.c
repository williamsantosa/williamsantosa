#include "quick.h"

#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t quick_moves = 0;
uint64_t quick_comparisons = 0;

uint64_t get_quick_moves(void) {
    return quick_moves;
}

uint64_t get_quick_comparisons(void) {
    return quick_comparisons;
}

int64_t partition(uint32_t *arr, int64_t lo, int64_t hi) {
    uint32_t pivot = arr[lo + ((hi - lo) / 2)]; // As it says in lab doc, prevents overflow
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        quick_comparisons++;
        i += 1;
        while (arr[i] < pivot) {
            quick_comparisons++;
            i += 1;
        }
        j -= 1;
        while (arr[j] > pivot) {
            quick_comparisons++;
            j -= 1;
        }
        if (i < j) {
            uint32_t temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            quick_moves += 3;
        }
    }
    return j;
}

void quick_sort(uint32_t *A, uint32_t n) {
    uint32_t left = 0;
    uint32_t right = n - 1;

    Stack *s = stack_create();
    stack_push(s, left);
    stack_push(s, right);

    bool stack_1 = false;
    bool stack_2 = false;

    while (stack_empty(s) != true) {
        quick_comparisons++;
        int64_t hi = 0;
        int64_t lo = 0;
        stack_1 = stack_pop(s, &hi);
        stack_2 = stack_pop(s, &lo);
        if (!stack_1 || !stack_2) {
            exit(0);
        }
        int64_t p = partition(A, lo, hi);
        quick_comparisons++;
        if ((p + 1) < hi) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
        quick_comparisons++;
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
    }
}
