#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(3, 250, "R");
    inf.readSpace();
    int C = inf.readInt(3, 250, "C");
    inf.readEoln();

    // Read the grid
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        // Read exactly C characters (anything), then we validate them
        string pattern = string("[^]{") + to_string(C) + "}";
        grid[i] = inf.readLine(pattern, ("row_" + to_string(i+1)).c_str());
        // Validate each character
        for (int j = 0; j < C; j++) {
            char ch = grid[i][j];
            ensuref(ch == '.' || ch == '#' || ch == 'o' || ch == 'v',
                    "Invalid character at row %d, col %d: '%c'", i+1, j+1, ch);
        }
    }

    // We must ensure no sheep 'o' or wolf 'v' is in a region that can escape.
    // A region is escape-able if it touches the boundary.
    vector<vector<bool>> vis(R, vector<bool>(C, false));
    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] != '#' && !vis[i][j]) {
                // BFS/DFS this component
                queue<pair<int,int>> q;
                q.push({i, j});
                vis[i][j] = true;

                bool touchesBoundary = false;
                bool hasSheep = false, hasWolf = false;

                while (!q.empty()) {
                    auto [r, c] = q.front(); q.pop();
                    if (r == 0 || r == R-1 || c == 0 || c == C-1) {
                        touchesBoundary = true;
                    }
                    if (grid[r][c] == 'o') hasSheep = true;
                    if (grid[r][c] == 'v') hasWolf = true;
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr >= 0 && nr < R && nc >= 0 && nc < C
                            && !vis[nr][nc] && grid[nr][nc] != '#') {
                            vis[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }

                // By problem statement, all sheep and wolves start in enclosed regions
                if (touchesBoundary) {
                    ensuref(!hasSheep && !hasWolf,
                            "Region starting at (%d,%d) touches boundary but contains %d sheep and %d wolves",
                            i+1, j+1, hasSheep ? 1 : 0, hasWolf ? 1 : 0);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
