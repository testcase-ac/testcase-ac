#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 50, "R");
    inf.readSpace();
    int c = inf.readInt(1, 50, "C");
    inf.readEoln();

    vector<string> grid(r);
    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken("[.XS]{1,50}", "row");
        ensuref((int)grid[i].size() == c, "row %d has length %d, expected %d",
                i + 1, (int)grid[i].size(), c);
        inf.readEoln();
    }
    inf.readEof();

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    vector<vector<int>> island(r, vector<int>(c, 0));
    int island_count = 0;

    for (int sr = 0; sr < r; ++sr) {
        for (int sc = 0; sc < c; ++sc) {
            if (grid[sr][sc] != 'X' || island[sr][sc] != 0) {
                continue;
            }

            ++island_count;
            queue<pair<int, int>> q;
            q.push({sr, sc});
            island[sr][sc] = island_count;

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = cr + dr[dir];
                    int nc = cc + dc[dir];
                    if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                        continue;
                    }
                    if (grid[nr][nc] == 'X' && island[nr][nc] == 0) {
                        island[nr][nc] = island_count;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    ensuref(1 <= island_count && island_count <= 15,
            "number of islands is %d, expected 1..15", island_count);

    vector<vector<bool>> reachable(r, vector<bool>(c, false));
    queue<pair<int, int>> q;
    bool started = false;
    for (int i = 0; i < r && !started; ++i) {
        for (int j = 0; j < c && !started; ++j) {
            if (grid[i][j] == 'X') {
                q.push({i, j});
                reachable[i][j] = true;
                started = true;
            }
        }
    }

    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nr = cr + dr[dir];
            int nc = cc + dc[dir];
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                continue;
            }
            if (grid[nr][nc] != '.' && !reachable[nr][nc]) {
                reachable[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            ensuref(grid[i][j] != 'X' || reachable[i][j],
                    "island cell (%d, %d) is not reachable through X/S cells",
                    i + 1, j + 1);
        }
    }
}
