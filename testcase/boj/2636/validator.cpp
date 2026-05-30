#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    vector<pair<int, int>> cheese;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int cell = inf.readInt(0, 1, "grid_cell");
            if (cell == 1) {
                cheese.push_back({i, j});
            }
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                ensuref(cell == 0,
                        "border cell at (%d,%d) must be 0 but found %d",
                        i, j, cell);
            }
            if (j + 1 < m) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    ensuref(!cheese.empty(), "the board must contain one piece of cheese");

    inf.readEof();
    return 0;
}
