#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<string> grid(m);
    for (int i = 0; i < m; ++i) {
        grid[i] = inf.readToken("[X.]{1,1000}", "row");
        inf.readEoln();
        ensuref((int)grid[i].size() == n, "row %d has length %d, expected %d",
                i + 1, (int)grid[i].size(), n);
    }

    for (int j = 0; j < n; ++j) {
        ensuref(grid[0][j] == 'X', "top border cell (%d, %d) is not X", 1, j + 1);
        ensuref(grid[m - 1][j] == 'X', "bottom border cell (%d, %d) is not X", m, j + 1);
    }
    for (int i = 0; i < m; ++i) {
        ensuref(grid[i][0] == 'X', "left border cell (%d, %d) is not X", i + 1, 1);
        ensuref(grid[i][n - 1] == 'X', "right border cell (%d, %d) is not X", i + 1, n);
    }

    inf.readEof();
}
