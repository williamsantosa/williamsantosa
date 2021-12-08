#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        if (oldspeak != NULL) {
            (n->oldspeak) = strdup(oldspeak);
        }
        if (newspeak != NULL) {
            (n->newspeak) = strdup(newspeak);
        }
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        if ((*n)->oldspeak != NULL) {
            free((*n)->oldspeak);
        }
        if ((*n)->newspeak != NULL) {
            free((*n)->newspeak);
        }
        free(*n);
    }
    n = NULL;
    return;
}

void node_print(Node *n) {
    if (n == NULL) {
        return;
    }
    if (n != NULL) {
        if (((n->newspeak) != NULL) && ((n->oldspeak) != NULL)) {
            printf("%s -> %s\n", (n->oldspeak), (n->newspeak));
        } else {
            printf("%s\n", n->oldspeak);
        }
    }
    return;
}
