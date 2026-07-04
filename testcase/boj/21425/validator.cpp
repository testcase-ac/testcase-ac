#include "testlib.h"

#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(2, 50, "h");
    inf.readSpace();
    int m = inf.readInt(2, 50, "m");
    inf.readSpace();
    int n = inf.readInt(2, 50, "n");
    inf.readEoln();

    vector<vector<string>> maze(h, vector<string>(m));
    int startCount = 0;
    int finishCount = 0;
    tuple<int, int, int> start{-1, -1, -1};
    tuple<int, int, int> finish{-1, -1, -1};
    string rowPattern = "[.o12]{" + to_string(n) + "," + to_string(n) + "}";

    for (int z = 0; z < h; ++z) {
        for (int r = 0; r < m; ++r) {
            maze[z][r] = inf.readToken(rowPattern, "level_row");
            inf.readEoln();
            for (int c = 0; c < n; ++c) {
                char cell = maze[z][r][c];
                if (cell == '1') {
                    ++startCount;
                    start = {z, r, c};
                    ensuref(z == 0, "start cell must be on the top level");
                } else if (cell == '2') {
                    ++finishCount;
                    finish = {z, r, c};
                    ensuref(z == h - 1, "finish cell must be on the bottom level");
                }
            }
        }
        // CHECK: The prose mentions blank lines between levels, but the official
        // sample has none, so this validator follows the materialized sample.
    }

    ensuref(startCount == 1, "expected exactly one start cell, found %d", startCount);
    ensuref(finishCount == 1, "expected exactly one finish cell, found %d", finishCount);

    vector<vector<vector<int>>> seen(h, vector<vector<int>>(m, vector<int>(n, 0)));
    queue<tuple<int, int, int>> q;
    q.push(start);
    seen[get<0>(start)][get<1>(start)][get<2>(start)] = 1;

    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [z, r, c] = q.front();
        q.pop();

        if (z + 1 < h && maze[z + 1][r][c] != 'o' && !seen[z + 1][r][c]) {
            seen[z + 1][r][c] = 1;
            q.push({z + 1, r, c});
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                continue;
            }
            if (maze[z][nr][nc] == 'o' || seen[z][nr][nc]) {
                continue;
            }
            seen[z][nr][nc] = 1;
            q.push({z, nr, nc});
        }
    }

    ensuref(seen[get<0>(finish)][get<1>(finish)][get<2>(finish)],
            "finish cell must be reachable from start");

    inf.readEof();
}
