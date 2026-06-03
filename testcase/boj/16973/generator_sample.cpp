#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void clearRect(vector<vector<int>>& grid, int r, int c, int h, int w) {
    for (int i = r; i < r + h; ++i) {
        for (int j = c; j < c + w; ++j) {
            grid[i][j] = 0;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int m = rnd.next(2, 14);

    if (mode == 1 && rnd.next(0, 1)) {
        n = rnd.next(2, 5);
        m = rnd.next(8, 18);
    } else if (mode == 1) {
        n = rnd.next(8, 18);
        m = rnd.next(2, 5);
    }

    int h = rnd.next(1, n);
    int w = rnd.next(1, m);
    if (mode == 2) {
        h = rnd.next(max(1, n - 3), n);
        w = rnd.next(1, m);
    } else if (mode == 3) {
        h = rnd.next(1, n);
        w = rnd.next(max(1, m - 3), m);
    } else if (mode == 4) {
        h = rnd.next(1, min(n, 3));
        w = rnd.next(1, min(m, 3));
    }

    int maxR = n - h + 1;
    int maxC = m - w + 1;
    int sr = rnd.next(1, maxR);
    int sc = rnd.next(1, maxC);
    int fr = rnd.next(1, maxR);
    int fc = rnd.next(1, maxC);

    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 0) {
        double density = rnd.next(0.0, 0.18);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = rnd.next() < density;
            }
        }
    } else if (mode == 1) {
        double density = rnd.next(0.10, 0.35);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = rnd.next() < density;
            }
        }
    } else if (mode == 2 && n >= 4) {
        int wallRow = rnd.next(1, n - 2);
        for (int c = 0; c < m; ++c) {
            grid[wallRow][c] = 1;
        }
        int gap = rnd.next(0, m - 1);
        grid[wallRow][gap] = 0;
        if (gap > 0 && rnd.next(0, 1)) grid[wallRow][gap - 1] = 0;
        if (gap + 1 < m && rnd.next(0, 1)) grid[wallRow][gap + 1] = 0;
    } else if (mode == 3 && m >= 4) {
        int wallCol = rnd.next(1, m - 2);
        for (int r = 0; r < n; ++r) {
            grid[r][wallCol] = 1;
        }
        int gap = rnd.next(0, n - 1);
        grid[gap][wallCol] = 0;
        if (gap > 0 && rnd.next(0, 1)) grid[gap - 1][wallCol] = 0;
        if (gap + 1 < n && rnd.next(0, 1)) grid[gap + 1][wallCol] = 0;
    } else if (mode == 4) {
        double density = rnd.next(0.25, 0.50);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = rnd.next() < density;
            }
        }
    }

    clearRect(grid, sr - 1, sc - 1, h, w);

    println(n, m);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }
    println(h, w, sr, sc, fr, fc);

    return 0;
}
