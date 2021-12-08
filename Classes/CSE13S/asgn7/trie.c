#include "trie.h"

#include "code.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
    TrieNode *TN = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (TN) {
        TN->code = code;
    }
    return TN;
}

void trie_node_delete(TrieNode *n) {
    if (n != NULL) {
        free(n);
        n = NULL;
    }
    return;
}

TrieNode *trie_create(void) {
    TrieNode *TN = trie_node_create(EMPTY_CODE);
    return TN;
}

// Same as trie_delete except you don't delete the root node
// Calls trie_delete for the children TrieNodes
void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i++) {
        if ((root->children[i]) != NULL) {
            trie_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }
    return;
}

void trie_delete(TrieNode *n) {
    for (int i = 0; i < ALPHABET; i++) {
        if ((n->children[i]) != NULL) {
            trie_delete(n->children[i]);
            n->children[i] = NULL;
        }
    }
    trie_node_delete(n);
    return;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n->children[sym];
}
