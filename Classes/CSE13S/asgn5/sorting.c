#include "bubble.h"
#include "comparisons.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqhr:n:p:"

typedef enum sorts_chosen { BUBBLE = 0, SHELL = 1, QUICK = 2, HEAP = 3 } sorts_chosen;

int seed = 7092016;
uint32_t size = 100;
uint32_t elements = 100;
int32_t temp = 0;
bool has_opt = false;

int main(int argc, char **argv) {
    int opt = 0;
    Set sorts = set_empty();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, QUICK);
            sorts = set_insert(sorts, HEAP);
            break;
        case 'b': sorts = set_insert(sorts, BUBBLE); break;
        case 's': sorts = set_insert(sorts, SHELL); break;
        case 'q': sorts = set_insert(sorts, QUICK); break;
        case 'h': sorts = set_insert(sorts, HEAP); break;
        case 'r': seed = atoi(optarg); break;
        case 'n':
            temp = atoi(optarg);
            if (temp <= 0 || ((uint32_t) temp) > UINT32_MAX) {
                fprintf(stderr, "Failed to allocate array to sort.\n");
                exit(0);
            }
            size = (uint32_t) temp;
            break;
        case 'p': elements = atoi(optarg); break;
        default:
            fprintf(stderr,
                "Select at least one sort to perform.\nSYNOPSIS\n   A collection of "
                "comparison-based sorting algorithms.\n\nUSAGE\n   ./sorting [-absqh] [-n length] "
                "[-p elements] [-r seed]\n\n OPTIONS\n   -a              Enable all sorts.\n   -b  "
                "            Enable bubble sort.\n   -s              Enable shell sort.\n   -q     "
                "         Enable Quick Sort.\n   -h              Enable Heap Sort.\n   -n length   "
                "    Specify number of array elements.\n   -p elements     Specify number of "
                "elements to print.\n   -r seed         Specify random seed.\n");
            exit(0);
        }
    }
    if (size < elements) {
        elements = size;
    }

    uint32_t *array = (uint32_t *) malloc(sizeof(uint32_t) * size);
    for (uint8_t f = BUBBLE; f <= HEAP; f++) {
        if (set_member(sorts, f)) {
            switch (f) {
            case BUBBLE: {
                printf("Bubble Sort\n");
                srandom(seed);
                // uint32_t array1[size];
                uint32_t temp = 0;
                for (uint32_t i = 0; i < size; i++) {
                    temp = random();
                    temp = temp & ~(1 << 31);
                    temp = temp & ~(1 << 30);
                    array[i] = temp;
                }
                bubble_sort(array, size);
                int number = 0;
                printf("%d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    get_bubble_moves(), get_bubble_comparisons());
                for (uint32_t i = 1; i <= elements; i++) {
                    if (number == 5) {
                        number = 0;
                        printf("\n");
                    }
                    printf("%13" PRIu32, array[i]);
                    number++;
                }
                printf("\n");
                has_opt = true;
                break;
            }
            case SHELL: {
                printf("Shell Sort\n");
                srandom(seed);
                //uint32_t array2[size];
                uint32_t temp = 0;
                for (uint32_t i = 0; i < size; i++) {
                    temp = random();
                    temp = temp & ~(1 << 31);
                    temp = temp & ~(1 << 30);
                    array[i] = temp;
                }
                shell_sort(array, size);
                int number = 0;
                printf("%d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    get_shell_moves(), get_shell_comparisons());
                for (uint32_t i = 0; i < elements; i++) {
                    if (number == 5) {
                        number = 0;
                        printf("\n");
                    }
                    printf("%13" PRIu32, array[i]);
                    number++;
                }
                printf("\n");
                has_opt = true;
                break;
            }
            case QUICK: {
                printf("Quick Sort\n");
                srandom(seed);
                // uint32_t array3[size];
                uint32_t temp = 0;
                for (uint32_t i = 0; i < size; i++) {
                    temp = random();
                    temp = temp & ~(1 << 31);
                    temp = temp & ~(1 << 30);
                    array[i] = temp;
                }
                quick_sort(array, size);
                int number = 0;
                printf("%d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    get_quick_moves(), get_quick_comparisons());
                for (uint32_t i = 0; i < elements; i++) {
                    if (number == 5) {
                        number = 0;
                        printf("\n");
                    }
                    printf("%13" PRIu32, array[i]);
                    number++;
                }
                printf("\n");
                has_opt = true;
                break;
            }
            case HEAP: {
                printf("Heap Sort\n");
                srandom(seed);
                // uint32_t array4[size];
                uint32_t temp = 0;
                for (uint32_t i = 0; i < size; i++) {
                    temp = random();
                    temp = temp & ~(1 << 31);
                    temp = temp & ~(1 << 30);
                    array[i] = temp;
                }
                heap_sort(array, size);
                int number = 0;
                printf("%d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
                    get_heap_moves(), get_heap_comparisons());
                for (uint32_t i = 0; i < elements; i++) {
                    if (number == 5) {
                        number = 0;
                        printf("\n");
                    }
                    printf("%13" PRIu32, array[i]);
                    number++;
                }
                printf("\n");
                has_opt = true;
                break;
            }
            }
        }
    }
    if (!has_opt) {
        fprintf(stderr,
            "Select at least one sort to perform.\nSYNOPSIS\n   A collection of "
            "comparison-based sorting algorithms.\n\nUSAGE\n   ./sorting [-absqh] [-n length] "
            "[-p elements] [-r seed]\n\n OPTIONS\n   -a              Enable all sorts.\n   -b  "
            "            Enable bubble sort.\n   -s              Enable shell sort.\n   -q     "
            "         Enable Quick Sort.\n   -h              Enable Heap Sort.\n   -n length   "
            "    Specify number of array elements.\n   -p elements     Specify number of "
            "elements to print.\n   -r seed         Specify random seed.\n");
        exit(0);
    }
    free(array);
    return 0;
}
