#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        grid[i] = inf.readToken("[X.]{1,50}", "row");
        ensuref((int)grid[i].size() == m,
                "row %d has length %d, expected %d", i + 1, (int)grid[i].size(), m);
        inf.readEoln();
    }

    vector<vector<int>> seen(n, vector<int>(m, 0));
    int components = 0;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] != 'X' || seen[r][c]) {
                continue;
            }

            ++components;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = cr + dr[dir];
                    int nc = cc + dc[dir];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                        continue;
                    }
                    if (grid[nr][nc] != 'X' || seen[nr][nc]) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    ensuref(components == 3, "grid has %d spots, expected exactly 3", components);
    inf.readEof();
}
