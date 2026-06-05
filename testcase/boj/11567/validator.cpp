#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        grid[i] = inf.readToken("[X.]{1,500}", "grid_row");
        ensuref((int)grid[i].size() == m, "grid row %d has length %d, expected %d",
                i + 1, (int)grid[i].size(), m);
        inf.readEoln();
    }

    int r1 = inf.readInt(1, n, "r1");
    inf.readSpace();
    int c1 = inf.readInt(1, m, "c1");
    inf.readEoln();

    int r2 = inf.readInt(1, n, "r2");
    inf.readSpace();
    inf.readInt(1, m, "c2");
    inf.readEoln();

    ensuref(grid[r1 - 1][c1 - 1] == 'X',
            "initial position (%d, %d) must be damaged ice X", r1, c1);

    inf.readEof();
}
