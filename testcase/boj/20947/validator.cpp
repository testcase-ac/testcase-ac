#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        grid[i] = inf.readToken("[.OX]{1,2000}", "row");
        ensuref((int)grid[i].size() == n, "row %d length is %d, expected %d", i + 1,
                (int)grid[i].size(), n);
        inf.readEoln();
    }
    inf.readEof();

    vector<vector<char>> unsafe(n, vector<char>(n, 0));

    for (int i = 0; i < n; ++i) {
        char last = 0;
        for (int j = 0; j < n; ++j) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }

        last = 0;
        for (int j = n - 1; j >= 0; --j) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        char last = 0;
        for (int i = 0; i < n; ++i) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }

        last = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }
    }

    vector<vector<char>> destroyed(n, vector<char>(n, 0));
    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != '.' || unsafe[i][j]) continue;

            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                while (0 <= ni && ni < n && 0 <= nj && nj < n && grid[ni][nj] == '.') {
                    ni += di[dir];
                    nj += dj[dir];
                }
                if (0 <= ni && ni < n && 0 <= nj && nj < n && grid[ni][nj] == 'X') {
                    destroyed[ni][nj] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ensuref(grid[i][j] != 'X' || destroyed[i][j],
                    "rubble at row %d column %d cannot be produced by any valid bomb", i + 1,
                    j + 1);
        }
    }
}
