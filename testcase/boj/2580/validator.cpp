#include "testlib.h"
#include <vector>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The Sudoku input is exactly 9 lines, each with 9 integers in [0,9], separated by single spaces,
    // no trailing spaces, and then a newline.
    const int N = 9;
    vector<array<int, N>> grid(N);

    // Read the 9 rows
    for (int i = 0; i < N; i++) {
        auto row = inf.readInts(N, 0, 9, "cell");
        // After exactly N tokens, we must be at end of line
        inf.readEoln();
        for (int j = 0; j < N; j++) {
            grid[i][j] = row[j];
        }
    }

    // No extra lines before EOF
    // Check row constraints: no duplicate non-zero in any row
    for (int i = 0; i < N; i++) {
        // pos[j] = column index where value j was first seen in row i
        array<int, N+1> pos;
        pos.fill(-1);
        for (int j = 0; j < N; j++) {
            int v = grid[i][j];
            if (v == 0) continue;
            if (pos[v] != -1) {
                // duplicate in row i at columns pos[v] and j
                ensuref(false,
                        "Duplicate value %d in row %d at columns %d and %d",
                        v, i+1, pos[v]+1, j+1);
            }
            pos[v] = j;
        }
    }

    // Check column constraints: no duplicate non-zero in any column
    for (int j = 0; j < N; j++) {
        array<int, N+1> pos;
        pos.fill(-1);
        for (int i = 0; i < N; i++) {
            int v = grid[i][j];
            if (v == 0) continue;
            if (pos[v] != -1) {
                ensuref(false,
                        "Duplicate value %d in column %d at rows %d and %d",
                        v, j+1, pos[v]+1, i+1);
            }
            pos[v] = i;
        }
    }

    // Check 3x3 box constraints
    for (int bi = 0; bi < 3; bi++) {
        for (int bj = 0; bj < 3; bj++) {
            // box starting at (bi*3, bj*3)
            array<int, N+1> pos;
            pos.fill(-1);
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    int i = bi*3 + di;
                    int j = bj*3 + dj;
                    int v = grid[i][j];
                    if (v == 0) continue;
                    if (pos[v] != -1) {
                        // compute previous cell coords
                        int pi = bi*3 + pos[v]/3;
                        int pj = bj*3 + pos[v]%3;
                        ensuref(false,
                                "Duplicate value %d in 3x3 box at cells (%d,%d) and (%d,%d)",
                                v, pi+1, pj+1, i+1, j+1);
                    }
                    // store flattened position di*3+dj
                    pos[v] = di*3 + dj;
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
