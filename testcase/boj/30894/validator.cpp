#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200, "n");
    inf.readSpace();
    int m = inf.readInt(2, 200, "m");
    inf.readEoln();

    int sx = inf.readInt(1, n, "sx");
    inf.readSpace();
    int sy = inf.readInt(1, m, "sy");
    inf.readSpace();
    int ex = inf.readInt(1, n, "ex");
    inf.readSpace();
    int ey = inf.readInt(1, m, "ey");
    inf.readEoln();

    ensuref(sx != ex || sy != ey, "entrance and exit must be distinct");

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        grid[i] = inf.readToken("[.#0123]{" + to_string(m) + "}", "row");
        inf.readEoln();
    }

    ensuref(grid[sx - 1][sy - 1] == '.', "entrance must be empty");
    ensuref(grid[ex - 1][ey - 1] == '.', "exit must be empty");

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            char cell = grid[x][y];
            if (cell < '0' || cell > '3') {
                continue;
            }

            int dir = cell - '0';
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            while (0 <= nx && nx < n && 0 <= ny && ny < m) {
                char seen = grid[nx][ny];
                if (seen == '#' || ('0' <= seen && seen <= '3')) {
                    break;
                }
                ensuref(nx != sx - 1 || ny != sy - 1,
                        "ghost at (%d, %d) sees the entrance at time 0", x + 1, y + 1);
                nx += dx[dir];
                ny += dy[dir];
            }
        }
    }

    inf.readEof();
}
