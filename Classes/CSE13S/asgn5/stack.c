#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top; // Points to next empty slot
    uint32_t capacity; // Number of items that can be pushed
    int64_t *items; // Pointer towards the items
};

Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    s->top = 0;
    s->capacity = MIN_CAPACITY;
    s->items = (int64_t *) calloc((s->capacity), sizeof(int64_t));
    return s;
}

void stack_delete(Stack **s) {
    free((*s)->items);
    free(*s);
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top == (s->capacity)) {
        s->capacity = 2 * (s->capacity);
        s->items = (int64_t *) realloc((s->items), (s->capacity) * sizeof(int64_t));
    }
    if (s->items == NULL) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    int count = 0;
    for (int64_t i = 0; i < (s->capacity); i++) {
        if (count == 5) {
            count = 0;
            printf("\n");
        }
        printf("%13" PRId64, (s->items[i]));
        count++;
    }
    printf("\n");
    return;
}
