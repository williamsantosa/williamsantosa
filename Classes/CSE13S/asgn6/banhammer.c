#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "h:f:m"
#define WORD    "([a-zA-Z0-9]+'?-?_?)+"

// Skeleton of the code from Eugene's lab section
int main(int argc, char **argv) {
    // Loop through getopt
    int opt = 0;
    uint32_t hash_size = 10000;
    uint32_t bf_size = 1048576;
    bool mtf = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            if (optarg == NULL || atoi(optarg) == 0) {
                fprintf(stderr, "Invalid hash table size.\n");
                exit(1);
            }
            hash_size = strtoul(optarg, NULL, 0);
            break;
        case 'f':
            if (optarg == NULL || atoi(optarg) == 0) {
                fprintf(stderr, "Invalid Bloom filter size.\n");
                exit(1);
            }
            bf_size = strtoul(optarg, NULL, 0);
            break;
        case 'm': mtf = true; break;
        default:
            printf("Usage: ./banhammer [-m] [-h size] [-f size]\n   -s          Print "
                   "statistics.\n   -m          Enable move-to-front rule.\n   -h size  "
                   "   Set hash table size.\n   -f size     Set Bloom filter size.\n");
            exit(0);
        }
    }

    // Initialize BF, HT, thoughtcrime, rightspeak
    BloomFilter *bf = bf_create(bf_size);
    HashTable *ht = ht_create(hash_size, mtf);
    LinkedList *thoughtcrime = ll_create(mtf);
    LinkedList *rightspeak = ll_create(mtf);

    // Error check for BF, HT, thoughtcrime, rightspeak
    if (bf == NULL) {
        fprintf(stderr, "Failed to create Bloom filter.\n");
        exit(1);
    } else if (ht == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        exit(1);
    } else if (thoughtcrime == NULL) {
        fprintf(stderr, "Failed to create thoughtcrime.\n");
        exit(1);
    } else if (rightspeak == NULL) {
        fprintf(stderr, "failed to create rightspeak.\n");
        exit(1);
    }

    // Open badspeak.txt and newspeak.txt
    FILE *badfile = fopen("badspeak.txt", "r");
    FILE *newfile = fopen("newspeak.txt", "r");

    // Error check for opening the badfile and newfile
    if (badfile == NULL) {
        bf_delete(&bf);
        ht_delete(&ht);
        ll_delete(&thoughtcrime);
        ll_delete(&rightspeak);
        fprintf(stderr, "Failed to open badspeak.txt.\n");
        exit(1);
    }
    if (newfile == NULL) {
        bf_delete(&bf);
        ht_delete(&ht);
        ll_delete(&thoughtcrime);
        ll_delete(&rightspeak);
        fprintf(stderr, "Failed to open newspeak.txt.\n");
        exit(1);
    }

    // Read badspeak from badspeak.txt
    // Insert oldspeak into BF and HT
    char badspeak[4000];
    while ((fscanf(badfile, "%s\n", badspeak)) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }

    // Read newspeak from newspeak.txt
    // Insert newspeak into BF and HT
    char newspeak[4000];
    while ((fscanf(newfile, "%s %s\n", badspeak, newspeak)) != EOF) {
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, newspeak);
    }

    // Use regex to parse stdin.
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        exit(1);
    }

    // Parse through standard input
    // Insert into thoughtcrime/rightspeak
    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        // Convert to lower case
        for (size_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word)) {
            if (ht_lookup(ht, word) != NULL) {
                Node *n = ht_lookup(ht, word);
                if (n->newspeak == NULL) {
                    ll_insert(thoughtcrime, n->oldspeak, NULL);
                } else {
                    ll_insert(rightspeak, n->oldspeak, n->newspeak);
                }
            }
        }
    }

    // Print out the error messages
    if (ll_length(thoughtcrime) != 0 && ll_length(rightspeak) != 0) {
        printf("Dear Comrade,\n\nYou have chosen to use degenerate words that may "
               "cause hurt\nfeelings or cause your comrades to think unpleasant "
               "thoughts.\nThis is doubleplus bad. To correct your wrongthink "
               "and\npreserve community consensus we will be sending you to "
               "joycamp\nadministered by Medellin's Miniluv. Beware of the "
               "hippos.\n\nYour errors:\n\n");
        ll_print(thoughtcrime);
        printf("\nThink of these words on your vacation!\n\n");
        ll_print(rightspeak);
    } else if (ll_length(thoughtcrime) != 0 && ll_length(rightspeak) == 0) {
        printf("Dear Comrade,\n\nYou have chosen to use degenerate words that may "
               "cause hurt\nfeelings or cause your comrades to think unpleasant "
               "thoughts.\nThis is doubleplus bad. To correct your wrongthink "
               "and\npreserve community consensus we will be sending you to "
               "joycamp\nadministered by Medellin's Miniluv. Beware of the "
               "hippos.\n\nYour errors:\n\n");
        ll_print(thoughtcrime);
    } else if (ll_length(thoughtcrime) == 0 && ll_length(rightspeak) != 0) {
        printf("Dear Comrade,\n\nSubmitting your text helps to preserve feelings "
               "and prevent\nbadthink. Some of the words that you used are not "
               "goodspeak.\nThe list shows how to turn the oldspeak words into "
               "newspeak.\n\n");
        ll_print(rightspeak);
    }

    // Free memory / Close stuff
    fclose(badfile);
    fclose(newfile);
    clear_words();
    regfree(&re);
    bf_delete(&bf);
    ht_delete(&ht);
    ll_delete(&thoughtcrime);
    ll_delete(&rightspeak);
    return 0;
}
