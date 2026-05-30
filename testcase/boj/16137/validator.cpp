#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

namespace {

int n;
int m;
vector<vector<int>> grid;

bool isCliffCell(int value) {
    return value != 1;
}

bool isBridgeCell(int value) {
    return value >= 2;
}

bool isCliffIntersection(int r, int c) {
    bool horizontal = false;
    bool vertical = false;

    if (c > 0 && isCliffCell(grid[r][c - 1])) {
        horizontal = true;
    }
    if (c + 1 < n && isCliffCell(grid[r][c + 1])) {
        horizontal = true;
    }
    if (r > 0 && isCliffCell(grid[r - 1][c])) {
        vertical = true;
    }
    if (r + 1 < n && isCliffCell(grid[r + 1][c])) {
        vertical = true;
    }

    return horizontal && vertical;
}

bool canPlaceNewBridge(int r, int c) {
    return grid[r][c] == 0 && !isCliffIntersection(r, c);
}

bool canReachAfterPlacingOneBridge() {
    struct State {
        int r;
        int c;
        int usedNewBridge;
    };

    vector<vector<array<bool, 2>>> visited(
        n, vector<array<bool, 2>>(n, {false, false}));
    queue<State> q;

    visited[0][0][0] = true;
    q.push({0, 0, 0});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.r == n - 1 && cur.c == n - 1) {
            return true;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nr = cur.r + dr[dir];
            int nc = cur.c + dc[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }

            bool fromBridge = isBridgeCell(grid[cur.r][cur.c]);
            bool toBridge = isBridgeCell(grid[nr][nc]);
            int nextUsedNewBridge = cur.usedNewBridge;

            if (grid[nr][nc] == 0) {
                if (cur.usedNewBridge || !canPlaceNewBridge(nr, nc)) {
                    continue;
                }
                toBridge = true;
                nextUsedNewBridge = 1;
            }

            if (fromBridge && toBridge) {
                continue;
            }

            if (!visited[nr][nc][nextUsedNewBridge]) {
                visited[nr][nc][nextUsedNewBridge] = true;
                q.push({nr, nc, nextUsedNewBridge});
            }
        }
    }

    return false;
}

} // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    n = inf.readInt(2, 10, "N");
    inf.readSpace();
    m = inf.readInt(2, 20, "M");
    inf.readEoln();

    grid.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        grid[i][0] = inf.readInt(0, 20, "cell");
        for (int j = 1; j < n; ++j) {
            inf.readSpace();
            grid[i][j] = inf.readInt(0, 20, "cell");
        }
        inf.readEoln();
    }

    ensuref(grid[0][0] == 1, "start cell must be ordinary land");
    ensuref(grid[n - 1][n - 1] == 1, "destination cell must be ordinary land");

    bool hasBuildableCliff = false;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (isBridgeCell(grid[r][c])) {
                ensuref(!isCliffIntersection(r, c),
                        "existing bridge at (%d,%d) is on a cliff intersection", r, c);
            }
            if (canPlaceNewBridge(r, c)) {
                hasBuildableCliff = true;
            }
        }
    }

    ensuref(hasBuildableCliff, "there must be at least one cliff where a new bridge can be placed");
    ensuref(canReachAfterPlacingOneBridge(), "destination must be reachable after placing one new bridge");

    inf.readEof();
}
