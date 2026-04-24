#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Total dimensions
    int total_rows = 5 * M + 1;
    int total_cols = 5 * N + 1;

    // Read all lines, check characters and border structure
    vector<string> grid;
    grid.reserve(total_rows);
    for (int i = 0; i < total_rows; i++) {
        // read a line containing only #, . or *
        string s = inf.readLine("[#.*]+", "row");
        // check length
        ensuref((int)s.size() == total_cols,
                "Line %d has length %d, expected %d", i, (int)s.size(), total_cols);
        // check each character
        if (i % 5 == 0) {
            // border row: all '#'
            for (int j = 0; j < total_cols; j++) {
                ensuref(s[j] == '#',
                        "Expected '#' at border row %d, col %d, got '%c'", i, j, s[j]);
            }
        } else {
            // interior row: at cols multiple of 5 '#', others '.' or '*'
            for (int j = 0; j < total_cols; j++) {
                if (j % 5 == 0) {
                    ensuref(s[j] == '#',
                            "Expected border '#' at row %d, col %d, got '%c'", i, j, s[j]);
                } else {
                    // content cell: must not be '#'
                    ensuref(s[j] == '.' || s[j] == '*',
                            "Unexpected character '%c' in window content at row %d, col %d", s[j], i, j);
                }
            }
        }
        grid.push_back(s);
    }

    // Check each 4x4 window matches one of the 5 allowed patterns
    // Patterns: k = number of top rows fully '*' (0..4), then remaining rows all '.'
    for (int wi = 0; wi < M; wi++) {
        for (int wj = 0; wj < N; wj++) {
            // compute starting cell of this window content
            int base_row = 1 + 5 * wi;
            int base_col = 1 + 5 * wj;
            // read the 4x4 block
            // first, count how many full '*' rows from top
            int k = 0;
            for (; k < 4; k++) {
                bool all_star = true;
                for (int c = 0; c < 4; c++) {
                    if (grid[base_row + k][base_col + c] != '*') {
                        all_star = false;
                        break;
                    }
                }
                if (!all_star) break;
            }
            // rows k..3 must be all '.'
            for (int r = k; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    ensuref(grid[base_row + r][base_col + c] == '.',
                            "Window at (%d,%d) has invalid '*' in row %d of block",
                            wi, wj, r);
                }
            }
            // k in [0,4] always, so by construction this enforces one of the 5 patterns
        }
    }

    inf.readEof();
    return 0;
}
