#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int R, C, K;
vector<string> grid;

// Directions: up, down, left, right
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// DFS to check if at least one path of length K exists from (R-1,0) to (0,C-1)
int dfs(int r, int c, int steps, vector<vector<bool>>& vis) {
    if (r == 0 && c == C-1) {
        return steps == K ? 1 : 0;
    }
    int cnt = 0;
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (grid[nr][nc] == 'T') continue;
        if (vis[nr][nc]) continue;
        vis[nr][nc] = true;
        cnt += dfs(nr, nc, steps+1, vis);
        vis[nr][nc] = false;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    R = inf.readInt(1, 5, "R");
    inf.readSpace();
    C = inf.readInt(1, 5, "C");
    inf.readSpace();
    K = inf.readInt(1, R*C, "K");
    inf.readEoln();

    grid.resize(R);
    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readLine("[.T]{"+to_string(C)+","+to_string(C)+"}", "row");
        ensuref((int)grid[i].size() == C, "Row %d does not have exactly C=%d characters", i+1, C);
        for (int j = 0; j < C; ++j) {
            ensuref(grid[i][j] == '.' || grid[i][j] == 'T', "Invalid character '%c' at row %d, col %d", grid[i][j], i+1, j+1);
        }
    }

    // Check that the starting and ending positions are not blocked
    ensuref(grid[R-1][0] == '.', "Starting position (row %d, col 1) must be '.'", R, 1);
    ensuref(grid[0][C-1] == '.', "Ending position (row 1, col %d) must be '.'", C);

    // Check that at least one path of length K exists from (R-1,0) to (0,C-1)
    vector<vector<bool>> vis(R, vector<bool>(C, false));
    vis[R-1][0] = true;
    int path_count = dfs(R-1, 0, 1, vis);
    ensuref(path_count > 0, "No path of length K=%d from start to end exists", K);

    inf.readEof();
}
