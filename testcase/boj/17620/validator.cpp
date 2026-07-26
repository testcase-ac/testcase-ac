#include "testlib.h"
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    vector<vector<int>> walls(n);
    for (int i = 0; i < n; ++i) {
        walls[i] = inf.readInts(n, 0, 15, "wall");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref((walls[0][i] & 1) != 0, "top boundary is open at column %d", i + 1);
        ensuref((walls[n - 1][i] & 4) != 0, "bottom boundary is open at column %d", i + 1);
        ensuref(i == 0 || (walls[i][0] & 8) != 0,
                "left boundary is open at row %d", i + 1);
        ensuref(i == n - 1 || (walls[i][n - 1] & 2) != 0,
                "right boundary is open at row %d", i + 1);
    }
    ensuref((walls[0][0] & 8) == 0, "entrance must be open");
    ensuref((walls[n - 1][n - 1] & 2) == 0, "exit must be open");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < n; ++j) {
            ensuref(bool(walls[i][j] & 2) == bool(walls[i][j + 1] & 8),
                    "inconsistent wall between (%d, %d) and (%d, %d)",
                    i + 1, j + 1, i + 1, j + 2);
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ensuref(bool(walls[i][j] & 4) == bool(walls[i + 1][j] & 1),
                    "inconsistent wall between (%d, %d) and (%d, %d)",
                    i + 1, j + 1, i + 2, j + 1);
        }
    }

    vector<vector<bool>> reachable(n, vector<bool>(n));
    queue<pair<int, int>> pending;
    reachable[0][0] = true;
    pending.push({0, 0});
    const int dr[] = {-1, 0, 1, 0};
    const int dc[] = {0, 1, 0, -1};
    const int bit[] = {1, 2, 4, 8};
    while (!pending.empty()) {
        auto [r, c] = pending.front();
        pending.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n ||
                (walls[r][c] & bit[d]) || reachable[nr][nc]) {
                continue;
            }
            reachable[nr][nc] = true;
            pending.push({nr, nc});
        }
    }
    ensuref(reachable[n - 1][n - 1], "exit is unreachable from the entrance");

    int m = inf.readInt(1, min(n * n, 100), "m");
    inf.readEoln();
    set<pair<int, int>> positions;
    set<int> reachableValues;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int c = inf.readInt(1, n * n, "c_i");
        inf.readEoln();
        ensuref(positions.insert({x, y}).second,
                "duplicate LED tile position at record %d: (%d, %d)", i + 1, x, y);
        if (reachable[x - 1][y - 1]) {
            reachableValues.insert(c);
        }
    }

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();
    int previous = -1;
    for (int i = 0; i < t; ++i) {
        int value = inf.readInt(1, n * n, "s_i");
        if (i + 1 < t) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
        ensuref(reachableValues.count(value),
                "sequence value %d at index %d has no reachable LED tile", value, i + 1);
        ensuref(value != previous,
                "equal adjacent sequence values at indices %d and %d", i, i + 1);
        previous = value;
    }

    inf.readEof();
}
