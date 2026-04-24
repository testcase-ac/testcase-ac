#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read grid: 0 = track (free), 1 = no track (blocked)
    vector<vector<int>> grid(M+1, vector<int>(N+1));
    for (int i = 1; i <= M; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "grid");
        inf.readEoln();
        for (int j = 1; j <= N; j++) {
            grid[i][j] = row[j-1];
        }
    }

    // Read start position and direction
    int sr = inf.readInt(1, M, "start_row");
    inf.readSpace();
    int sc = inf.readInt(1, N, "start_col");
    inf.readSpace();
    int sd = inf.readInt(1, 4, "start_dir"); // 1=east,2=west,3=south,4=north
    inf.readEoln();

    // Read target position and direction
    int tr = inf.readInt(1, M, "target_row");
    inf.readSpace();
    int tc = inf.readInt(1, N, "target_col");
    inf.readSpace();
    int td = inf.readInt(1, 4, "target_dir");
    inf.readEoln();

    // Start and target cells must be on track (grid == 0)
    ensuref(grid[sr][sc] == 0,
            "Start cell (%d, %d) is blocked (must be 0)", sr, sc);
    ensuref(grid[tr][tc] == 0,
            "Target cell (%d, %d) is blocked (must be 0)", tr, tc);

    // Check connectivity by simple BFS on 4-neighbors
    vector<vector<bool>> seen(M+1, vector<bool>(N+1, false));
    queue<pair<int,int>> q;
    seen[sr][sc] = true;
    q.push({sr, sc});
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 1 && nr <= M && nc >= 1 && nc <= N
                && !seen[nr][nc] && grid[nr][nc] == 0) {
                seen[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    ensuref(seen[tr][tc],
            "No path from start (%d, %d) to target (%d, %d)", sr, sc, tr, tc);

    inf.readEof();
    return 0;
}
