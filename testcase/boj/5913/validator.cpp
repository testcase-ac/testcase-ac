#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const int N = 5;
static const int TOTAL = N * N;

int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(0, 22, "K");
    inf.readEoln();
    ensuref(K % 2 == 0, "K must be even, got %d", K);

    // Grid: true if there's a rock (no apple tree)
    bool rock[N+1][N+1] = {};
    // Track duplicates
    bool usedCell[N+1][N+1] = {};

    for (int t = 0; t < K; ++t) {
        int x = inf.readInt(1, 5, "x");
        inf.readSpace();
        int y = inf.readInt(1, 5, "y");
        inf.readEoln();

        ensuref(!(x == 1 && y == 1), "(1,1) must always have a tree, cannot be rock");
        ensuref(!(x == 5 && y == 5), "(5,5) must always have a tree, cannot be rock");
        ensuref(!usedCell[x][y], "Duplicate rock position at (%d,%d)", x, y);
        usedCell[x][y] = true;
        rock[x][y] = true;
    }

    // Check that start and end cells are not rocks (already ensured) and are within grid
    ensuref(!rock[1][1], "Cell (1,1) must contain an apple tree");
    ensuref(!rock[5][5], "Cell (5,5) must contain an apple tree");

    // Check that the graph of tree cells is connected (using only tree cells)
    // First, build list of tree cells
    vector<pair<int,int>> cells;
    cells.reserve(TOTAL - K);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (!rock[i][j]) cells.push_back({i,j});
        }
    }

    // BFS from (1,1) over tree cells
    bool vis[N+1][N+1] = {};
    queue<pair<int,int>> q;
    if (!rock[1][1]) {
        vis[1][1] = true;
        q.push({1,1});
    }

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];
            if (ni < 1 || ni > N || nj < 1 || nj > N) continue;
            if (rock[ni][nj]) continue;
            if (!vis[ni][nj]) {
                vis[ni][nj] = true;
                q.push({ni, nj});
            }
        }
    }

    // All tree cells must be reachable from (1,1), and in particular (5,5) must be reachable
    int treeCount = (int)cells.size();
    int visCount = 0;
    for (auto &p : cells) {
        if (vis[p.first][p.second]) ++visCount;
    }

    ensuref(vis[5][5], "(5,5) must be reachable from (1,1) through tree cells");
    ensuref(visCount == treeCount,
            "All tree cells must be connected via tree-adjacent moves: reachable=%d, total trees=%d",
            visCount, treeCount);

    // Optional: verify that "answer always exists" if that was a statement.
    // The original statement doesn't explicitly guarantee existence of a valid harvesting strategy,
    // only asks to count possible ways, so we do not need to compute/check existence here.

    inf.readEof();
}
