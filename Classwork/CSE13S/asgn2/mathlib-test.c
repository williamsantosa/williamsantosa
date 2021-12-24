#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// Heavily influenced by Eugene's Lab Section on 1/19/21, around 40 minutes in (go code)

#define OPTIONS "asctel"

int main(int argc, char **argv) {
    int opt = 0; // The option used
    bool do_sin, do_cos, do_tan, do_exp, do_log; // Sets if you should do one of these or not
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // Taken from Eugene's session
        switch (opt) {
        case 'a':
            do_sin = true;
            do_cos = true;
            do_tan = true;
            do_exp = true;
            do_log = true;
            break; // Breaks otherwise runs through everything below it, same with below
        case 's': do_sin = true; break;
        case 'c': do_cos = true; break;
        case 't': do_tan = true; break;
        case 'e': do_exp = true; break;
        case 'l': do_log = true; break;
        default:
            fprintf(stderr,
                "Usage: %s -[asctel]\n  -a           runs all tests (sin, cos, tan, exp, log)\n  "
                "-s           runs sin tests\n  -c           runs cos tests\n  -t           runs "
                "tan tests\n  -e           runs exp tests\n  -l           runs log tests\n",
                argv[0]);
        }
    }

    if (do_sin) {
        printf("  x            Sin              Library        Difference\n");
        printf("  -            ---              ------         ----------\n");
        double n = -2.0 * M_PI;
        // Pretty self explanatory, has the bounds above and below. Prints out x, sin, library, and difference.
        // The ones below function the same way.
        while (n < 2.0 * M_PI) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf \n", n, Sin(n), sin(n), (Sin(n) - sin(n)));
            n += 0.1;
        }
    }
    if (do_cos) {
        printf("  x            Cos              Library        Difference\n");
        printf("  -            ---              ------         ----------\n");
        double n = -2.0 * M_PI;
        while (n < 2.0 * M_PI) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf \n", n, Cos(n), cos(n), (Cos(n) - cos(n)));
            n += 0.1;
        }
    }
    if (do_tan) {
        printf("  x            Tan              Library        Difference\n");
        printf("  -            ---              ------         ----------\n");
        double n = -1.0 / 3.0 * M_PI;
        while (n < 1.0 / 3.0 * M_PI) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf \n", n, Tan(n), tan(n), (Tan(n) - tan(n)));
            n += 0.1;
        }
    }
    if (do_exp) {
        printf("  x            Exp              Library        Difference\n");
        printf("  -            ---              ------         ----------\n");
        double n = 1.0;
        while (n < 10.0) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf \n", n, Exp(n), exp(n), (Exp(n) - exp(n)));
            n += 0.1;
        }
    }
    if (do_log) {
        printf("  x            Log              Library        Difference\n");
        printf("  -            ---              ------         ----------\n");
        double n = 1.0;
        while (n < 10.0) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf \n", n, Log(n), log(n), (Log(n) - log(n)));
            n += 0.1;
        }
    }
    return 0;
}
