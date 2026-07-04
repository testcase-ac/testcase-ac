#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool isCouchCell(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    vector<string> grid(n);
    for (int r = 0; r < n; ++r) {
        grid[r] = inf.readToken("[.A-Za-z]{1,1000}", "row");
        ensuref((int)grid[r].size() == m, "row %d has length %d, expected %d", r + 1, (int)grid[r].size(), m);
        inf.readEoln();
    }

    vector<vector<int>> seen(n, vector<int>(m, 0));
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '.' || seen[r][c]) {
                continue;
            }

            char ch = grid[r][c];
            ensuref(isCouchCell(ch), "invalid couch character '%c' at row %d column %d", ch, r + 1, c + 1);

            vector<pair<int, int>> cells;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;

            while (!q.empty()) {
                auto [vr, vc] = q.front();
                q.pop();
                cells.push_back({vr, vc});

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = vr + dr[dir];
                    int nc = vc + dc[dir];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m || seen[nr][nc] || grid[nr][nc] != ch) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }

            ensuref(cells.size() == 2,
                    "couch component for '%c' starting at row %d column %d has %d cells, expected 2",
                    ch, r + 1, c + 1, (int)cells.size());
            ensuref(cells[0].first == cells[1].first || cells[0].second == cells[1].second,
                    "couch component for '%c' starting at row %d column %d is not adjacent",
                    ch, r + 1, c + 1);
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '.') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m || grid[nr][nc] == '.') {
                    continue;
                }
                if (grid[nr][nc] != grid[r][c]) {
                    continue;
                }

                // Same-character neighbors must be the two cells of one couch, not adjacent distinct couches.
                int sameNeighbors = 0;
                for (int otherDir = 0; otherDir < 4; ++otherDir) {
                    int rr = r + dr[otherDir];
                    int cc = c + dc[otherDir];
                    if (0 <= rr && rr < n && 0 <= cc && cc < m && grid[rr][cc] == grid[r][c]) {
                        ++sameNeighbors;
                    }
                }
                ensuref(sameNeighbors == 1,
                        "cell at row %d column %d touches more than its paired couch cell", r + 1, c + 1);
            }
        }
    }

    inf.readEof();
}
