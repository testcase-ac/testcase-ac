#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 738, "R");
    inf.readSpace();
    int c = inf.readInt(1, 738, "C");
    inf.readEoln();

    vector<string> grid(r);
    int rampCells = 0;
    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken("[?\\.1#PB]{1,738}", "room_row");
        inf.readEoln();
        ensuref((int)grid[i].size() == c,
                "row %d has length %d, expected %d", i + 1, (int)grid[i].size(), c);

        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == '?') {
                ++rampCells;
                ensuref(rampCells <= 18, "number of '?' cells exceeds 18");
            }
        }
    }

    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] != '?') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + dx[dir];
                int nj = j + dy[dir];
                if (0 <= ni && ni < r && 0 <= nj && nj < c) {
                    ensuref(grid[ni][nj] != '?',
                            "'?' cells are adjacent at (%d, %d) and (%d, %d)",
                            i + 1, j + 1, ni + 1, nj + 1);
                }
            }
        }
    }

    int x = inf.readInt(1, r, "x");
    inf.readSpace();
    int y = inf.readInt(1, c, "y");
    inf.readEoln();

    char start = grid[x - 1][y - 1];
    ensuref(start != '#' && start != '?',
            "start cell (%d, %d) must not be '#' or '?'", x, y);

    inf.readEof();
}
