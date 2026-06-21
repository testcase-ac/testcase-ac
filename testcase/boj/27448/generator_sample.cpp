#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void putCell(vector<string>& grid, int r, int c) {
    if (0 <= r && r < (int)grid.size() && 0 <= c && c < (int)grid[0].size()) {
        grid[r][c] = '#';
    }
}

void fillRect(vector<string>& grid, int r1, int c1, int r2, int c2) {
    for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c) {
            putCell(grid, r, c);
        }
    }
}

void ensureWood(vector<string>& grid) {
    bool hasWood = false;
    for (const string& row : grid) {
        hasWood = hasWood || row.find('#') != string::npos;
    }
    if (!hasWood) {
        putCell(grid, rnd.next((int)grid.size()), rnd.next((int)grid[0].size()));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(2, 16);
    int m = rnd.next(2, 16);
    if (mode == 6) {
        n = rnd.next(1, 5);
        m = rnd.next(40, 80);
    } else if (mode == 7) {
        n = rnd.next(40, 80);
        m = rnd.next(1, 5);
    }
    int f = rnd.next(1, 80);
    vector<string> grid(n, string(m, '.'));

    if (mode == 0) {
        int r1 = rnd.next(n);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(m);
        int c2 = rnd.next(c1, m - 1);
        fillRect(grid, r1, c1, r2, c2);
    } else if (mode == 1) {
        int step = rnd.next(1, 4);
        bool horizontal = rnd.next(2) == 0;
        if (horizontal) {
            int offset = rnd.next(step);
            for (int r = offset; r < n; r += step) {
                for (int c = 0; c < m; ++c) putCell(grid, r, c);
            }
        } else {
            int offset = rnd.next(step);
            for (int c = offset; c < m; c += step) {
                for (int r = 0; r < n; ++r) putCell(grid, r, c);
            }
        }
    } else if (mode == 2) {
        int count = rnd.next(1, min(n * m, 30));
        vector<pair<int, int>> cells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) cells.push_back({r, c});
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < count; ++i) putCell(grid, cells[i].first, cells[i].second);
    } else if (mode == 3) {
        int r = rnd.next(n);
        int c = rnd.next(m);
        int steps = rnd.next(1, min(80, n * m));
        for (int i = 0; i < steps; ++i) {
            putCell(grid, r, c);
            int dir = rnd.next(4);
            if (dir == 0) r = max(0, r - 1);
            if (dir == 1) r = min(n - 1, r + 1);
            if (dir == 2) c = max(0, c - 1);
            if (dir == 3) c = min(m - 1, c + 1);
        }
    } else if (mode == 4) {
        int r1 = rnd.next(0, max(0, n - 2));
        int c1 = rnd.next(0, max(0, m - 2));
        int r2 = rnd.next(r1 + 1, n - 1);
        int c2 = rnd.next(c1 + 1, m - 1);
        for (int c = c1; c <= c2; ++c) {
            putCell(grid, r1, c);
            putCell(grid, r2, c);
        }
        for (int r = r1; r <= r2; ++r) {
            putCell(grid, r, c1);
            putCell(grid, r, c2);
        }
    } else if (mode == 5) {
        int parity = rnd.next(2);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (((r + c) & 1) == parity) putCell(grid, r, c);
            }
        }
    } else {
        int segments = rnd.next(1, 8);
        for (int i = 0; i < segments; ++i) {
            int r1 = rnd.next(n);
            int r2 = rnd.next(r1, n - 1);
            int c1 = rnd.next(m);
            int c2 = rnd.next(c1, m - 1);
            fillRect(grid, r1, c1, r2, c2);
        }
    }

    ensureWood(grid);
    println(n, m, f);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
