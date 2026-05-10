#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y;
    vector<vector<bool>> vis;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_PATHS = 100000;

    int caseCnt = 0;

    while (!inf.eof()) {
        if (inf.seekEof())
            break;

        ++caseCnt;
        ensuref(caseCnt <= MAX_T, "Too many test cases: %d > %d", caseCnt, MAX_T);

        int N = inf.readInt(1, 30, "N");
        inf.readSpace();
        int M = inf.readInt(1, 30, "M");
        inf.readEoln();

        vector<string> board(N);
        int emptyCnt = 0;
        for (int i = 0; i < N; ++i) {
            board[i] = inf.readToken("[.*]{1,30}", "row");
            inf.readEoln();
            ensuref((int)board[i].size() == M,
                    "Row %d length mismatch: expected %d, got %d", i, M, (int)board[i].size());
            for (int j = 0; j < M; ++j) {
                char c = board[i][j];
                ensuref(c == '.' || c == '*',
                        "Invalid cell character at (%d,%d): '%c'", i, j, c);
                if (c == '.') emptyCnt++;
            }
        }

        ensuref(emptyCnt > 0, "Board with only obstacles is not allowed");

        // Global property: number of possible movement paths <= 1,000,000
        // Interpret as: number of distinct complete visiting paths (from any start)
        // We brute force DFS over all starts, counting complete paths with pruning.

        int totalCells = N * M;
        int maxPaths = MAX_PATHS;
        int pathCount = 0;

        // directions: up, down, left, right
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        auto inBounds = [&](int x, int y) {
            return x >= 0 && x < N && y >= 0 && y < M;
        };

        function<void(int,int,vector<vector<bool>>&,int)> dfs =
            [&](int x, int y, vector<vector<bool>>& vis, int visitedCnt) {
                if (pathCount > maxPaths) return;

                bool anyMove = false;

                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];

                    // Check if immediate neighbor allows movement
                    if (!inBounds(nx, ny)) continue;
                    if (board[nx][ny] == '*') continue;
                    if (vis[nx][ny]) continue;

                    anyMove = true;

                    // simulate sliding
                    int cx = x, cy = y;
                    vector<pair<int,int>> pathCells;
                    int add = 0;

                    while (true) {
                        int tx = cx + dx[dir];
                        int ty = cy + dy[dir];
                        if (!inBounds(tx, ty)) break;
                        if (board[tx][ty] == '*') break;
                        if (vis[tx][ty]) break;
                        cx = tx; cy = ty;
                        vis[cx][cy] = true;
                        pathCells.emplace_back(cx, cy);
                        add++;
                    }

                    if (add > 0) {
                        dfs(cx, cy, vis, visitedCnt + add);

                        // backtrack
                        for (auto &p : pathCells) {
                            vis[p.first][p.second] = false;
                        }
                    }
                }

                if (!anyMove) {
                    if (visitedCnt == emptyCnt) {
                        pathCount++;
                    }
                }
            };

        // For every empty cell as starting point
        for (int i = 0; i < N && pathCount <= maxPaths; ++i) {
            for (int j = 0; j < M && pathCount <= maxPaths; ++j) {
                if (board[i][j] != '.') continue;
                vector<vector<bool>> vis(N, vector<bool>(M, false));
                vis[i][j] = true;
                dfs(i, j, vis, 1);
            }
        }

        ensuref(pathCount <= maxPaths,
                "Number of possible complete visiting paths exceeds 1,000,000: %d", pathCount);
    }

    inf.readEof();
}
