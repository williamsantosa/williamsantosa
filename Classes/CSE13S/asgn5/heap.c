#include "heap.h"

#include "comparisons.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t heap_moves = 0;
uint64_t heap_comparisons = 0;

uint64_t get_heap_moves(void) {
    return heap_moves;
}

uint64_t get_heap_comparisons(void) {
    return heap_comparisons;
}

uint32_t max_child(uint32_t *arr, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    heap_comparisons++;
    if ((right <= last) && (arr[right - 1] > arr[left - 1])) {
        return right;
    }
    return left;
}

void fix_heap(uint32_t *arr, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t parent = first;
    uint32_t great = max_child(arr, parent, last);

    while ((parent <= (last / 2)) && !found) {
        heap_comparisons++;
        if (arr[parent - 1] < arr[great - 1]) {
            heap_moves += 3;
            uint32_t temp = arr[parent - 1];
            arr[parent - 1] = arr[great - 1];
            arr[great - 1] = temp;
            parent = great;
            great = max_child(arr, parent, last);
        } else {
            found = true;
        }
    }
}

void build_heap(uint32_t *arr, uint32_t first, uint32_t last) {
    for (uint32_t parent = (last / 2); parent > (first - 1); parent--) {
        fix_heap(arr, parent, last); // Might be wrong here, parent might refer to array value
    }
}

void heap_sort(uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf--) {
        heap_moves += 3;
        uint32_t temp = A[first - 1];
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = temp;
        fix_heap(A, first, leaf - 1);
    }
}
