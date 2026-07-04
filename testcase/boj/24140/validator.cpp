#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int w = inf.readInt(1, 100, "W");
    inf.readSpace();
    int h = inf.readInt(1, 100, "H");
    inf.readEoln();

    vector<vector<int>> grid(h, vector<int>(w));
    vector<int> minRow(n + 1, h), maxRow(n + 1, -1);
    vector<int> minCol(n + 1, w), maxCol(n + 1, -1);
    int visibleCells = 0;

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            if (c > 0) {
                inf.readSpace();
            }
            int color = inf.readInt(0, n, format("C[%d][%d]", r + 1, c + 1).c_str());
            grid[r][c] = color;
            if (color != 0) {
                ++visibleCells;
                minRow[color] = min(minRow[color], r);
                maxRow[color] = max(maxRow[color], r);
                minCol[color] = min(minCol[color], c);
                maxCol[color] = max(maxCol[color], c);
            }
        }
        inf.readEoln();
    }

    ensuref(visibleCells > 0, "at least one paper cell must be visible");

    vector<vector<int>> above(n + 1);
    vector<vector<bool>> hasEdge(n + 1, vector<bool>(n + 1, false));
    vector<int> indegree(n + 1, 0);

    for (int color = 1; color <= n; ++color) {
        if (maxRow[color] == -1) {
            continue;
        }
        for (int r = minRow[color]; r <= maxRow[color]; ++r) {
            for (int c = minCol[color]; c <= maxCol[color]; ++c) {
                int visible = grid[r][c];
                ensuref(visible != 0,
                        "table color inside bounding rectangle of color %d at row %d column %d",
                        color, r + 1, c + 1);
                if (visible != color && !hasEdge[color][visible]) {
                    hasEdge[color][visible] = true;
                    above[color].push_back(visible);
                    ++indegree[visible];
                }
            }
        }
    }

    queue<int> q;
    for (int color = 1; color <= n; ++color) {
        if (indegree[color] == 0) {
            q.push(color);
        }
    }

    int removed = 0;
    while (!q.empty()) {
        int color = q.front();
        q.pop();
        ++removed;
        for (int next : above[color]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    ensuref(removed == n, "visible paper overlap constraints must be acyclic");

    inf.readEof();
}
