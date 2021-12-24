#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *l = (LinkedList *) malloc(sizeof(LinkedList));
    if (l) {
        l->length = 0;
        l->mtf = mtf;
        l->head = node_create(NULL, NULL);
        l->tail = node_create(NULL, NULL);
        l->head->next = l->tail;
        l->tail->prev = l->head;
    }
    return l;
}
void ll_delete(LinkedList **ll) {
    while (((*ll)->head) != NULL) {
        Node *next = (((*ll)->head)->next);
        node_delete(&((*ll)->head));
        ((*ll)->head) = next;
    }
    free(*ll);
    ll = NULL;
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return (ll->length);
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    if (ll == NULL || oldspeak == NULL) {
        return NULL;
    }
    for (Node *curr = (ll->head); curr != NULL; curr = curr->next) {
        if (((curr->oldspeak) != NULL) && strcmp(curr->oldspeak, oldspeak) == 0) {
            if (ll->mtf) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->prev = ll->head;
                curr->next = ll->head->next;
                ll->head->next->prev = curr;
                ll->head->next = curr;
            }
            return curr;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    Node *check = ll_lookup(ll, oldspeak);
    if (check != NULL) {
        return;
    }
    Node *n = node_create(oldspeak, newspeak);
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next->prev = n;
    ll->head->next = n;
    ll->length += 1;
    return;
}

void ll_print(LinkedList *ll) {
    if (ll != NULL) {
        for (Node *curr = (ll->head->next); (curr->next) != NULL; curr = curr->next) {
            node_print(curr);
        }
    }
}
