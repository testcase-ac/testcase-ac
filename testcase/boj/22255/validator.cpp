#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    int sx = inf.readInt(1, n, "sx");
    inf.readSpace();
    int sy = inf.readInt(1, m, "sy");
    inf.readSpace();
    int ex = inf.readInt(1, n, "ex");
    inf.readSpace();
    int ey = inf.readInt(1, m, "ey");
    inf.readEoln();

    ensuref(sx != ex || sy != ey, "start and end must be different: (%d, %d)", sx, sy);

    vector<vector<int>> grid(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            grid[i][j] = inf.readInt(-1, 300, "cell");
        }
        inf.readEoln();
    }

    ensuref(grid[sx][sy] == 0, "start cell must have impact 0, found %d", grid[sx][sy]);
    ensuref(grid[ex][ey] == 0, "end cell must have impact 0, found %d", grid[ex][ey]);

    inf.readEof();
}
