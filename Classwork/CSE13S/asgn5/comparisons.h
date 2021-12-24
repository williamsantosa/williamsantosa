#ifndef __COMPARISONS_H__
#define __COMPARISONS_H__

uint64_t bubble_moves;
uint64_t bubble_comparisons;

uint64_t shell_moves;
int64_t shell_comparisons;

uint64_t quick_moves;
uint64_t quick_comparisons;

uint64_t heap_moves;
uint64_t heap_comparisons;

uint64_t get_bubble_moves(void);
uint64_t get_bubble_comparisons(void);

uint64_t get_shell_moves(void);
uint64_t get_shell_comparisons(void);

uint64_t get_quick_moves(void);
uint64_t get_quick_comparisons(void);

uint64_t get_heap_moves(void);
uint64_t get_heap_comparisons(void);

#endif
