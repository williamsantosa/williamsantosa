#include "names.h" // Required file (Vampire  Names & Roll Names)

#include <inttypes.h>
#include <limits.h> // LIMITS STUFF
#include <stdio.h> // For basic usage
#include <stdlib.h> // Math stuff

// KNOWN BUGS HERE
// Input 2.5 and it still works
// Input 2a and it still works
// Input any number for randSeed and it'll still work
//
//
//

// Initialize global variables
int numPlayers = 0;
u_int32_t randSeed = 0;

// Important Functions
int roll(void) // Inspired by Eugene's Lab session, making a roll function
{
    return (random() % 6);
}

int left(int position, int players) // Included in the lab document
{
    return ((position + players - 1) % players);
}

int right(int position, int players) // Included in the lab document
{
    return ((position + 1) % players);
}

// Main Program
int main(void) {
    // Obtain numPlayers
    // Credit for scan and checking numPlayers / randSeed goes to Eugene's lab
    // session on 1/12/2021 Around 37 minutes into his lecture

    printf("Number of players: ");
    if (scanf("%d", &numPlayers) != 1) {
        fprintf(stderr, "Invalid number of players.\n");
        exit(1);
    }

    if (numPlayers < 2 || numPlayers > 10) {
        fprintf(stderr, "Invalid number of players.\n");
        exit(1);
    }

    // Obtain randSeed
    printf("Random seed: ");
    if (scanf("%u", &randSeed) != 1) {
        fprintf(stderr, "Invalid random seed.\n");
        exit(1);
    }

    if (randSeed < 0 || randSeed > UINT32_MAX) {
        fprintf(stderr, "Invalid random seed.\n");
        exit(1);
    }

    srandom(randSeed); // Sets the random seed to randSeed

    // Initialize variables
    int numLives[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        numLives[i] = 3;
    }
    int roundNumber = 1;
    int rollOne = 0; // First roll
    int rollTwo = 0; // Second roll
    int lowRoll = 0; // Player index lowest roll
    int lowRollNumber = 0; // Lowest total number
    int rollNumber = 0; // Roll number
    int playersAlive = numPlayers;
    int champion = 0; // Index of latest alive player

    // Loop game
    do {
        printf("Round %d\n", roundNumber); // Print round number
        lowRollNumber = 100;
        for (int i = 0; i < numPlayers;
             i++) // Prints name and what they rolled, checks roll and replaces if
        // roll < lowRoll
        {
            if (numLives[i] < 1) {
                continue;
            }
            rollOne = roll();
            rollTwo = roll();
            rollNumber = (rollOne + rollTwo);
            if (rollNumber < lowRollNumber) {
                lowRollNumber = rollNumber;
                lowRoll = i;
            }
            printf(" - %s rolls %s...", names[i], rolls[rollOne][rollTwo]);
            if (rollNumber == 10) {
                numLives[left(i, numPlayers)]++;
                numLives[right(i, numPlayers)]++;
                if (numLives[left(i, numPlayers)]
                    == 1) // Adds the sparkly effect after print for left side
                {
                    printf(" resurrects %s", names[left(i, numPlayers)]);
                } else {
                    printf(" sparkles %s", names[left(i, numPlayers)]);
                }
                if (numLives[right(i, numPlayers)]
                    == 1) // Adds the sparkly effect after print for right side
                {
                    printf(" resurrects %s", names[right(i, numPlayers)]);
                } else {
                    printf(" sparkles %s", names[right(i, numPlayers)]);
                }
            }
            printf("\n");
        }
        numLives[lowRoll]--; // Decreases vampire amount of lives
        printf("%s is forced to eat garlic!\n", names[lowRoll]); // Prints above
        if (numLives[lowRoll] < 1) // If dead, does one of the stuff below
        {
            printf("%s has died.\n", names[lowRoll]);
        } else if (numLives[lowRoll] == 1) {
            printf("%s has 1 life remaining.\n", names[lowRoll]);
        } else {
            printf("%s has %d lives remaining.\n", names[lowRoll], numLives[lowRoll]);
        }
        roundNumber++; // Increment round
        playersAlive = 0;
        for (int i = 0; i < numPlayers; i++) // Checks for champion
        {
            if (numLives[i] > 0) {
                playersAlive++;
                champion = i;
            }
        }
        if (playersAlive < 2) {
            printf("%s wins the Garlic game!\n", names[champion]);
            exit(0);
        }
    } while (playersAlive > 1);

    return 0; // return 0, not error
}
