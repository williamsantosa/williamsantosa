#include "universe.h"

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

/* Some of the pseudocode was provided during Sahiti and Eugene's lectures and I would like to credit both of them for that
 * (Mostly for the uv_populate and uv_census pictures)
 */

struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

// Will return the specificied toroidal index value given value and totalValue
int convert(int value, int totalValue) {
    return ((value >= 0) || (value % totalValue == 0)) ? (value % totalValue)
                                                       : ((value % totalValue) + totalValue);
}

Universe *uv_create(int rows, int cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (int r = 0; r < rows; r++) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

// Returns toroidal value in universe u
bool toro(Universe *u) {
    return u->toroidal;
}

void uv_delete(Universe *u) {
    for (int r = 0; r < (u->rows); r++) {
        free(u->grid[r]);
    }
    free(u->grid);
    free(u);
    return;
}

int uv_rows(Universe *u) {
    return u->rows;
}

int uv_cols(Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, int r, int c) {
    if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
        return;
    } else {
        u->grid[r][c] = true;
    }
    return;
}

void uv_dead_cell(Universe *u, int r, int c) {
    if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
        return;
    } else {
        u->grid[r][c] = false;
    }
    return;
}

bool uv_get_cell(Universe *u, int r, int c) {
    if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
        return false;
    } else {
        return u->grid[r][c];
    }
    return false;
}

bool uv_populate(Universe *u, FILE *infile) {
    int r, c = 0;
    int numberScanned = 0;
    while ((numberScanned = fscanf(infile, "%d %d\n", &r, &c)) != -1) {
        if (numberScanned != 2) {
            printf("Malformed input.\n");
            exit(0);
        }
        if (toro(u)) {
            convert(r, uv_rows(u));
            convert(c, uv_cols(u));
        }
        if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
            return false;
        }
        u->grid[r][c] = true;
    }
    return true;
}

int uv_census(Universe *u, int r, int c) {
    int rv = 0;
    if (toro(u)) {
        if (uv_get_cell(u, convert(r - 1, uv_rows(u)), convert(c - 1, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r - 1, uv_rows(u)), convert(c, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r - 1, uv_rows(u)), convert(c + 1, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r, uv_rows(u)), convert(c - 1, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r, uv_rows(u)), convert(c + 1, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r + 1, uv_rows(u)), convert(c - 1, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r + 1, uv_rows(u)), convert(c, uv_cols(u))) == true) {
            rv++;
        }
        if (uv_get_cell(u, convert(r + 1, uv_rows(u)), convert(c + 1, uv_cols(u))) == true) {
            rv++;
        }
    } else {
        if (uv_get_cell(u, r - 1, c - 1) == true) {
            rv++;
        }
        if (uv_get_cell(u, r - 1, c) == true) {
            rv++;
        }
        if (uv_get_cell(u, r - 1, c + 1) == true) {
            rv++;
        }
        if (uv_get_cell(u, r, c - 1) == true) {
            rv++;
        }
        if (uv_get_cell(u, r, c + 1) == true) {
            rv++;
        }
        if (uv_get_cell(u, r + 1, c - 1) == true) {
            rv++;
        }
        if (uv_get_cell(u, r + 1, c) == true) {
            rv++;
        }
        if (uv_get_cell(u, r + 1, c + 1) == true) {
            rv++;
        }
    }
    return rv;
}

void uv_print(Universe *u, FILE *outfile) {
    for (int r = 0; r < uv_rows(u); r++) {
        for (int c = 0; c < uv_cols(u); c++) {
            if (uv_get_cell(u, r, c) == true) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
    return;
}
