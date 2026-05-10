#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    // Read the maze grid
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        // Read a line of 0/1 characters, length up to 100
        string s = inf.readLine("[01]{1,100}", "row");
        ensuref((int)s.size() == m,
                "Row %d: expected length %d but got %d",
                i+1, m, (int)s.size());
        grid[i] = s;
    }

    // Start and end must be open (1) to allow a path
    ensuref(grid[0][0] == '1', "Start cell (1,1) must be '1'");
    ensuref(grid[n-1][m-1] == '1', "End cell (N,M) must be '1'");

    // Check reachability via BFS on cells == '1'
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<pair<int,int>> q;
    vis[0][0] = true;
    q.push({0, 0});
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m
                && !vis[nr][nc] && grid[nr][nc] == '1') {
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    ensuref(vis[n-1][m-1],
            "Destination (N,M) is not reachable from (1,1)");

    inf.readEof();
    return 0;
}
