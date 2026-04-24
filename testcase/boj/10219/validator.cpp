#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T (no explicit upper bound in statement, assume up to 100k)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Read H, W
        int H = inf.readInt(1, 11, "H");
        inf.readSpace();
        int W = inf.readInt(1, 11, "W");
        inf.readEoln();
        // Read the grid
        vector<string> g(H);
        for (int i = 0; i < H; ++i) {
            // each row: only '.', 'a'..'z', length 1..11
            g[i] = inf.readLine("[.a-z]{1,11}", "grid_row");
            ensuref((int)g[i].size() == W,
                    "Test case %d, row %d: expected width %d but got %d",
                    tc, i+1, W, (int)g[i].size());
        }
        // Collect positions of each letter
        vector<vector<pair<int,int>>> pos(26);
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                char ch = g[r][c];
                if (ch != '.') {
                    pos[ch - 'a'].push_back({r, c});
                }
            }
        }
        // For each letter, ensure its cells form exactly one 4-connected component
        for (int letter = 0; letter < 26; ++letter) {
            int total = pos[letter].size();
            if (total == 0) continue;
            // BFS from the first occurrence
            vector<vector<bool>> seen(H, vector<bool>(W, false));
            queue<pair<int,int>> q;
            auto start = pos[letter][0];
            seen[start.first][start.second] = true;
            q.push(start);
            int cnt = 0;
            static const int dr[4] = {-1,1,0,0};
            static const int dc[4] = {0,0,-1,1};
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                ++cnt;
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < H && nc >= 0 && nc < W
                        && !seen[nr][nc]
                        && g[nr][nc] == char('a' + letter)) {
                        seen[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
            ensuref(cnt == total,
                    "Test case %d: letter '%c' has %d cells but BFS reached %d (not connected)",
                    tc, char('a'+letter), total, cnt);
        }
    }
    inf.readEof();
    return 0;
}
