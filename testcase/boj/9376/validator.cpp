#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read h and w
        int h = inf.readInt(2, 100, "h");
        inf.readSpace();
        int w = inf.readInt(2, 100, "w");
        inf.readEoln();

        vector<string> grid(h);
        int prisoner_count = 0;
        vector<pair<int,int>> prisoners;
        // Read grid rows
        string pattern = "[.*#$]{" + to_string(w) + "," + to_string(w) + "}";
        for (int i = 0; i < h; i++) {
            string row = inf.readLine(pattern, "grid_row");
            // Count prisoners and record positions
            for (int j = 0; j < w; j++) {
                char c = row[j];
                if (c == '$') {
                    prisoner_count++;
                    prisoners.emplace_back(i, j);
                }
            }
            grid[i] = row;
        }
        ensuref(prisoner_count == 2,
                "Test case %d: exactly two prisoners required, found %d",
                tc+1, prisoner_count);

        // Build padded grid for BFS (to represent outside)
        int H = h + 2, W = w + 2;
        vector<vector<char>> pd(H, vector<char>(W, '.'));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                pd[i+1][j+1] = grid[i][j];
            }
        }

        // BFS from outside (0,0)
        vector<vector<bool>> vis(H, vector<bool>(W, false));
        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0] = true;
        const int dr[4] = { -1, 1, 0, 0 };
        const int dc[4] = { 0, 0, -1, 1 };
        while (!q.empty()) {
            auto [r,c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
                if (vis[nr][nc]) continue;
                char cell = pd[nr][nc];
                if (cell == '*') continue; // wall
                // otherwise '.', '#', or '$' are passable
                vis[nr][nc] = true;
                q.push({nr,nc});
            }
        }

        // Check connectivity: each prisoner must reach outside
        for (int k = 0; k < 2; k++) {
            int gi = prisoners[k].first;
            int gj = prisoners[k].second;
            int pi = gi + 1, pj = gj + 1;
            ensuref(vis[pi][pj],
                    "Test case %d: prisoner at (%d,%d) cannot reach outside",
                    tc+1, gi+1, gj+1);
        }
    }

    inf.readEof();
    return 0;
}
