#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 20, "N");
    inf.readEoln();

    // Read grid rows
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        // Each row must consist only of 'E' or 'H'
        grid[i] = inf.readLine("[EH]+", "row");
        // Check length exactly N
        ensuref((int)grid[i].size() == N,
                "Length of row %d is %d, expected %d", i, (int)grid[i].size(), N);
        // No further per-char check needed; regex "[EH]+" ensures each char is E or H
    }

    // Validate start and end cells
    // Start: bottom-left at (row N-1, col 0)
    char startCell = grid[N-1][0];
    ensuref(startCell == 'E',
            "Start cell (row %d, col %d) is '%c', expected 'E'",
            N-1, 0, startCell);
    // End: top-right at (row 0, col N-1)
    char endCell = grid[0][N-1];
    ensuref(endCell == 'E',
            "End cell (row %d, col %d) is '%c', expected 'E'",
            0, N-1, endCell);

    // Check connectivity: there must be a path of 'E' cells from start to end
    vector<vector<bool>> vis(N, vector<bool>(N, false));
    queue<pair<int,int>> q;
    q.emplace(N-1, 0);
    vis[N-1][0] = true;
    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                if (!vis[nr][nc] && grid[nr][nc] == 'E') {
                    vis[nr][nc] = true;
                    q.emplace(nr, nc);
                }
            }
        }
    }
    ensuref(vis[0][N-1],
            "No path of 'E' cells from start (row %d, col %d) to end (row %d, col %d)",
            N-1, 0, 0, N-1);

    inf.readEof();
    return 0;
}
