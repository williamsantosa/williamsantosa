#define OPTIONS "tsn:i:o:"
#define ROW     0
#define DELAY   50000
#include "universe.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool toroidal = false;
bool silence = false;
int generations = 100;
FILE *infile;
FILE *outfile;
int rows = 0;
int cols = 0;

int main(int argc, char **argv) {
    infile = stdin;
    outfile = stdout;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': silence = true; break;
        case 'n': generations = atoi(optarg); break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                printf("Error opening %s.\n", optarg);
                stderr;
                exit(0);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                stderr;
                exit(0);
            }
            break;
        }
    }

    fscanf(infile, "%d %d\n", &rows, &cols);

    if (rows < 1 || cols < 1) {
        printf("Malformed input.\n");
        stderr;
        exit(0);
    }

    Universe *a = uv_create(rows, cols, toroidal);
    Universe *b = uv_create(rows, cols, toroidal);

    uv_populate(a, infile);

    if (silence == false) {
        initscr();
        curs_set(FALSE);
    }

    int count = 0;
    // Went through each generation, row, and column
    for (int i = 0; i < generations; i++) {
        // Refresh and resets count
        for (int r = 0; r < uv_rows(a); r++) {
            // Checks game of life rules and updates accordingly, prints to ncurses
            for (int c = 0; c < uv_cols(a); c++) {
                count = uv_census(a, r, c);
                if (uv_get_cell(a, r, c) == true && (count == 2 || count == 3)) {
                    uv_live_cell(b, r, c);
                    mvprintw(r, c, "o");
                } else if (uv_get_cell(a, r, c) == false && count == 3) {
                    uv_live_cell(b, r, c);
                    mvprintw(r, c, "o");
                } else {
                    uv_dead_cell(b, r, c);
                }
                count = 0;
            }
            refresh();
        }
        if (silence == false) {
            usleep(DELAY);
            clear();
        }
        // Swap a and b
        Universe *temp = a;
        a = b;
        b = temp;
    }

    if (silence == false) {
        endwin();
    }

    uv_print(a, outfile);
    uv_delete(a);
    uv_delete(b);
    fclose(infile);
    fclose(outfile);
    return 0;
}
