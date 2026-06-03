#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 32, "N");
    inf.readEoln();

    vector<vector<int>> grid(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (c > 0) {
                inf.readSpace();
            }
            grid[r][c] = inf.readInt(0, 1, "cell");
        }
        inf.readEoln();
    }

    ensuref(grid[0][0] == 0, "(1, 1) must be empty");
    ensuref(grid[0][1] == 0, "(1, 2) must be empty");

    inf.readEof();
}
