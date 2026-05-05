#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();
    ensuref(1LL * N * M <= 100000LL, "N*M must be <= 100000, got %d*%d=%lld", N, M, 1LL * N * M);

    vector<string> grid(N);
    int hCount = 0;
    int pCount = 0;
    int exitCount = 0;
    int hx = -1, hy = -1;
    vector<pair<int,int>> exits;

    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readToken("[HP#\\.X]{1,100000}", "row"); // length bound will be checked below
        inf.readEoln();
        ensuref((int)grid[i].size() == M, "Row %d must have length %d, got %d", i + 1, M, (int)grid[i].size());

        for (int j = 0; j < M; ++j) {
            char c = grid[i][j];
            if (c == 'H') {
                ++hCount;
                hx = i;
                hy = j;
            } else if (c == 'P') {
                ++pCount;
            } else if (c == '#') {
                ++exitCount;
                exits.push_back({i, j});
            } else if (c == '.' || c == 'X') {
                // ok
            } else {
                ensuref(false, "Invalid character '%c' at (%d,%d)", c, i, j);
            }
        }
    }

    ensuref(hCount == 1, "There must be exactly one 'H', found %d", hCount);
    ensuref(pCount >= 1 && pCount <= 100, "Number of 'P' cells must be between 1 and 100, found %d", pCount);
    ensuref(exitCount <= 100, "Number of '#' cells must be at most 100, found %d", exitCount);
    ensuref(exitCount >= 1, "There must be at least one exit '#' in the maze");

    // BFS from H to check reachability of at least one exit and for later distance use.
    const int INF = (int)1e9;
    vector<int> dist(N * M, INF);
    auto inside = [&](int x, int y) {
        return 0 <= x && x < N && 0 <= y && y < M;
    };
    queue<pair<int,int>> q;

    dist[hx * M + hy] = 0;
    q.push({hx, hy});

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        int d = dist[x * M + y];
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (!inside(nx, ny)) continue;
            if (grid[nx][ny] == 'X') continue; // walls are not passable
            int id = nx * M + ny;
            if (dist[id] > d + 1) {
                dist[id] = d + 1;
                q.push({nx, ny});
            }
        }
    }

    bool reachableExit = false;
    for (auto [ex, ey] : exits) {
        if (dist[ex * M + ey] < INF) {
            reachableExit = true;
            break;
        }
    }
    ensuref(reachableExit, "At least one exit '#' must be reachable from 'H'");

    inf.readEof();
}
