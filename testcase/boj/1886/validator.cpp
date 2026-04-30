#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 12, "N");
    inf.readSpace();
    int M = inf.readInt(3, 12, "M");
    inf.readEoln();

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        // Read exactly M chars consisting of X, ., D
        grid[i] = inf.readToken("[X.D]{1,12}", "row");
        inf.readEoln();
        ensuref((int)grid[i].size() == M,
                "Row %d must have exactly %d characters, but has %d",
                i + 1, M, (int)grid[i].size());
        for (int j = 0; j < M; ++j) {
            char c = grid[i][j];
            ensuref(c == 'X' || c == '.' || c == 'D',
                    "Invalid character '%c' at (%d,%d); must be 'X', '.' or 'D'",
                    c, i + 1, j + 1);
        }
    }

    // Problem constraints:
    // - Grid border cells must be wall 'X' or exit 'D'
    // - No exits 'D' in interior
    // - At least one empty cell '.'
    int dots = 0;
    int exits = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char c = grid[i][j];
            if (c == '.') dots++;
            if (c == 'D') exits++;

            bool border = (i == 0 || i == N - 1 || j == 0 || j == M - 1);
            if (border) {
                ensuref(c == 'X' || c == 'D',
                        "Border cell (%d,%d) must be 'X' or 'D', but is '%c'",
                        i + 1, j + 1, c);
            } else {
                ensuref(c == 'X' || c == '.',
                        "Interior cell (%d,%d) must be 'X' or '.', but is '%c'",
                        i + 1, j + 1, c);
            }
        }
    }
    ensuref(dots >= 1, "There must be at least one empty cell '.' in the grid");
    // exits may be zero (allowed)

    inf.readEof();
}
