#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m, n, q
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    // Read grid
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = inf.readInt(1, 1000000, "h_ij");
            if (j + 1 < n) inf.readSpace();
        }
        inf.readEoln();
    }

    // Read queries
    for (int i = 0; i < q; ++i) {
        int x1 = inf.readInt(1, m, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, n, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, m, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, n, "y2");
        inf.readEoln();
        // No further check needed, as all coordinates are in bounds
    }

    inf.readEof();
}
