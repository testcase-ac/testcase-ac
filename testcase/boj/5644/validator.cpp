#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int H = 20;
const int W = 20;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 200, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string blank = inf.readLine("[ ]*", "blank_line_before_case");
        ensuref(blank.empty(), "blank line before case %d must not contain spaces", tc);

        vector<string> grid(H);
        int totalX = 0;
        for (int r = 0; r < H; ++r) {
            grid[r] = inf.readLine("[.x]{20}", "grid_row");
            for (char c : grid[r]) {
                totalX += (c == 'x');
            }
        }
        ensuref(totalX == 25, "case %d has %d x cells, expected 25", tc, totalX);

        vector<vector<int>> seen(H, vector<int>(W, 0));
        int components = 0;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        for (int sr = 0; sr < H; ++sr) {
            for (int sc = 0; sc < W; ++sc) {
                if (grid[sr][sc] != 'x' || seen[sr][sc]) {
                    continue;
                }

                ++components;
                int minR = sr, maxR = sr, minC = sc, maxC = sc, cells = 0;
                queue<pair<int, int>> q;
                q.push({sr, sc});
                seen[sr][sc] = 1;

                while (!q.empty()) {
                    auto [r, c] = q.front();
                    q.pop();
                    ++cells;
                    minR = min(minR, r);
                    maxR = max(maxR, r);
                    minC = min(minC, c);
                    maxC = max(maxC, c);

                    for (int dir = 0; dir < 4; ++dir) {
                        int nr = r + dr[dir];
                        int nc = c + dc[dir];
                        if (nr < 0 || nr >= H || nc < 0 || nc >= W) {
                            continue;
                        }
                        if (grid[nr][nc] == 'x' && !seen[nr][nc]) {
                            seen[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }

                int rectangleArea = (maxR - minR + 1) * (maxC - minC + 1);
                ensuref(cells == rectangleArea,
                        "component %d in case %d is not a filled rectangle", components, tc);
            }
        }

        ensuref(components <= 5, "case %d has %d continents, expected at most 5", tc, components);
    }

    inf.readEof();
}
