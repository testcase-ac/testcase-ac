#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int r, c;
};

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    // u, v, w, x, y are positive integers; problem gives no upper bound, so assume int
    int u = inf.readInt(1, INT_MAX, "u");
    inf.readSpace();
    int v = inf.readInt(1, INT_MAX, "v");
    inf.readSpace();
    int w = inf.readInt(1, INT_MAX, "w");
    inf.readSpace();
    int x = inf.readInt(1, INT_MAX, "x");
    inf.readSpace();
    int y = inf.readInt(1, INT_MAX, "y");
    inf.readEoln();

    // Read board with strict spacing: n lines, each with n integers 0/1 separated by single spaces
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        a[i][0] = inf.readInt(0, 1, "cell");
        for (int j = 1; j < n; ++j) {
            inf.readSpace();
            a[i][j] = inf.readInt(0, 1, "cell");
        }
        inf.readEoln();
    }

    // Now validate global properties implied by the statement:
    // 1) All placed blocks are 'ㄷ'-shaped (C-shaped) blocks.
    // 2) They are mutually non-adjacent (no two cells of different blocks are edge-adjacent).

    vector<vector<int>> comp(n, vector<int>(n, -1));
    int compCnt = 0;
    vector<vector<Point>> cells; // cells per component

    auto inside = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    };

    // BFS to find connected components of 1-cells
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1 && comp[i][j] == -1) {
                queue<Point> q;
                q.push({i,j});
                comp[i][j] = compCnt;
                cells.push_back({});
                cells.back().push_back({i,j});
                while (!q.empty()) {
                    Point p = q.front(); q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nr = p.r + dr[d];
                        int nc = p.c + dc[d];
                        if (inside(nr, nc) && a[nr][nc] == 1 && comp[nr][nc] == -1) {
                            comp[nr][nc] = compCnt;
                            q.push({nr, nc});
                            cells.back().push_back({nr, nc});
                        }
                    }
                }
                ++compCnt;
            }
        }
    }

    // 2) Check that different components are not edge-adjacent
    // Since each component is maximal 4-connected region of 1s, any edge-adjacent 1s are in same comp already.
    // We instead ensure there are no edge-adjacent 1-cells belonging to different components (should be impossible)
    // and especially that different components are not touching via sharing a side via 0-cells (which can't happen).
    // The statement "서로 인접해있지 않다" means no two blocks share an edge: so no 1-cells of different components
    // can be edge-adjacent.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] != 1) continue;
            for (int d = 0; d < 4; ++d) {
                int ni = i + dr[d];
                int nj = j + dc[d];
                if (!inside(ni, nj)) continue;
                if (a[ni][nj] != 1) continue;
                ensuref(comp[ni][nj] == comp[i][j],
                        "Different blocks are edge-adjacent at (%d,%d) and (%d,%d)",
                        i, j, ni, nj);
            }
        }
    }

    // 1) Each component must be a 'ㄷ' block: a rectangle minus a smaller rectangle that shares exactly one side.
    // Definition in grid terms:
    // - Let outer bounding box [R1..R2] x [C1..C2]; all 1-cells lie on this box except for a single axis-aligned
    //   inner rectangle [r1..r2] x [c1..c2] that is fully zero inside the box.
    // - The inner rectangle must touch exactly one side of the outer bounding box, i.e. either r1 == R1 or r2 == R2
    //   or c1 == C1 or c2 == C2; and strictly inside on the other axis (R1 < r1 <= r2 < R2 or similar).
    // - No other 0-cells are allowed inside the outer box besides that inner rectangle.
    //
    // We verify this combinatorially per component.

    for (int id = 0; id < compCnt; ++id) {
        auto &vec = cells[id];
        // Compute outer bounding box
        int R1 = n, R2 = -1, C1 = n, C2 = -1;
        for (auto &p : vec) {
            R1 = min(R1, p.r);
            R2 = max(R2, p.r);
            C1 = min(C1, p.c);
            C2 = max(C2, p.c);
        }
        ensuref(R2 >= R1 && C2 >= C1, "Component %d has invalid bounds", id);

        int H = R2 - R1 + 1;
        int W = C2 - C1 + 1;

        // Map of filled cells within bounding box
        vector<vector<int>> box(H, vector<int>(W, 0));
        for (auto &p : vec) {
            box[p.r - R1][p.c - C1] = 1;
        }

        int totalArea = H * W;
        int ones = (int)vec.size();
        int zeros = totalArea - ones;
        ensuref(zeros > 0, "Component %d is full rectangle; not a C-shape", id);

        // Identify all zero cells inside box, they must form a single solid rectangle
        int zr1 = H, zr2 = -1, zc1 = W, zc2 = -1;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (box[i][j] == 0) {
                    zr1 = min(zr1, i);
                    zr2 = max(zr2, i);
                    zc1 = min(zc1, j);
                    zc2 = max(zc2, j);
                }
            }
        }
        ensuref(zr2 >= zr1 && zc2 >= zc1,
                "Component %d has inconsistent zero area", id);

        int innerH = zr2 - zr1 + 1;
        int innerW = zc2 - zc1 + 1;
        ensuref(innerH * innerW == zeros,
                "Component %d has holes that are not a single rectangle", id);

        // Check that every cell in inner rectangle is zero (already implied but double-check)
        for (int i = zr1; i <= zr2; ++i)
            for (int j = zc1; j <= zc2; ++j)
                ensuref(box[i][j] == 0,
                        "Component %d inner area not all zeros at local (%d,%d)",
                        id, i, j);

        // Now inner rectangle must share exactly one side with outer box
        bool touchTop = (zr1 == 0);
        bool touchBottom = (zr2 == H - 1);
        bool touchLeft = (zc1 == 0);
        bool touchRight = (zc2 == W - 1);
        int touches = (int)touchTop + (int)touchBottom + (int)touchLeft + (int)touchRight;

        ensuref(touches == 1,
                "Component %d inner rectangle must touch exactly one side of outer box", id);

        // And inner rectangle must be strictly inside on the other axis (not spanning full box)
        if (touchTop || touchBottom) {
            ensuref(zc1 > 0 && zc2 < W - 1,
                    "Component %d inner rectangle touching horizontal side must be strictly inside vertically", id);
        }
        if (touchLeft || touchRight) {
            ensuref(zr1 > 0 && zr2 < H - 1,
                    "Component %d inner rectangle touching vertical side must be strictly inside horizontally", id);
        }
    }

    inf.readEof();
}
