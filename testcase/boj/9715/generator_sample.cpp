#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Grid = vector<string>;

void setCell(Grid& grid, int r, int c, int height) {
    grid[r][c] = char('0' + height);
}

Grid makeSingle() {
    int r = 1;
    int c = 1;
    Grid grid(r, string(c, '0'));
    setCell(grid, 0, 0, rnd.next(1, 9));
    return grid;
}

Grid makeStrip() {
    bool horizontal = rnd.next(0, 1);
    int len = rnd.next(2, 18);
    Grid grid(horizontal ? 1 : len, string(horizontal ? len : 1, '0'));
    int base = rnd.next(1, 9);
    for (int i = 0; i < len; ++i) {
        int height = rnd.next(0, 2) == 0 ? base : rnd.next(1, 9);
        if (horizontal) {
            setCell(grid, 0, i, height);
        } else {
            setCell(grid, i, 0, height);
        }
    }
    return grid;
}

Grid makeFilledRectangle() {
    int r = rnd.next(2, 8);
    int c = rnd.next(2, 8);
    Grid grid(r, string(c, '0'));
    int mode = rnd.next(0, 3);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int height;
            if (mode == 0) {
                height = rnd.next(1, 9);
            } else if (mode == 1) {
                height = 1 + (i + j + rnd.next(0, 2)) % 9;
            } else if (mode == 2) {
                height = 1 + min({i, j, r - 1 - i, c - 1 - j}) % 9;
            } else {
                height = rnd.next(1, 3) == 1 ? 9 : rnd.next(1, 4);
            }
            setCell(grid, i, j, height);
        }
    }
    return grid;
}

Grid makeBlob() {
    int r = rnd.next(4, 10);
    int c = rnd.next(4, 10);
    int target = rnd.next(3, min(35, r * c));
    Grid grid(r, string(c, '0'));
    vector<pair<int, int>> cells;
    cells.push_back({rnd.next(0, r - 1), rnd.next(0, c - 1)});
    setCell(grid, cells[0].first, cells[0].second, rnd.next(1, 9));

    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    while ((int)cells.size() < target) {
        auto [row, col] = rnd.any(cells);
        vector<pair<int, int>> candidates;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            if (nr < 0 || nr >= r || nc < 0 || nc >= c || grid[nr][nc] != '0') {
                continue;
            }
            candidates.push_back({nr, nc});
        }
        if (candidates.empty()) {
            continue;
        }
        auto [nr, nc] = rnd.any(candidates);
        setCell(grid, nr, nc, rnd.next(1, 9));
        cells.push_back({nr, nc});
    }
    return grid;
}

Grid makeRing() {
    int r = rnd.next(3, 8);
    int c = rnd.next(3, 8);
    Grid grid(r, string(c, '0'));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i == 0 || j == 0 || i == r - 1 || j == c - 1) {
                setCell(grid, i, j, rnd.next(1, 9));
            }
        }
    }
    if (rnd.next(0, 1)) {
        int row = rnd.next(1, r - 2);
        for (int j = 1; j < c - 1; ++j) {
            setCell(grid, row, j, rnd.next(1, 9));
        }
    }
    if (rnd.next(0, 1)) {
        int col = rnd.next(1, c - 2);
        for (int i = 1; i < r - 1; ++i) {
            setCell(grid, i, col, rnd.next(1, 9));
        }
    }
    return grid;
}

Grid makeCase(int index) {
    if (index == 0) {
        return makeSingle();
    }
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return makeStrip();
    }
    if (mode == 1) {
        return makeFilledRectangle();
    }
    if (mode == 2) {
        return makeBlob();
    }
    return makeRing();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        Grid grid = makeCase(caseIndex);
        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
