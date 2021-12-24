#include "set.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t Set;

Set set_empty(void) {
    return 0;
}

bool set_member(Set s, uint8_t x) {
    Set mask = 1 << (x % 32);
    return (s & mask);
}

Set set_insert(Set s, uint8_t x) {
    Set mask = 1 << (x % 32);
    return (s | mask);
}

Set set_remove(Set s, uint8_t x) {
    Set mask = ~(1 << (x));
    return (s & mask);
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_complement(Set s) {
    return ~s;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}
