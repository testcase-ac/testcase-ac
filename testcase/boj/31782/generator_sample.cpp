#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int m = 1;
    vector<string> grid;

    if (mode == 0) {
        n = rnd.next(1, 14);
        m = 1;
        if (rnd.next(0, 1)) swap(n, m);
        grid.assign(n, string(m, '.'));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < 0.35) grid[i][j] = 'O';
            }
        }
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        grid.assign(n, string(m, '.'));

        if (mode == 1) {
            double p = rnd.next(0.05, 0.35);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (rnd.next() < p) grid[i][j] = 'O';
                }
            }
        } else if (mode == 2) {
            double p = rnd.next(0.60, 0.92);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (rnd.next() < p) grid[i][j] = 'O';
                }
            }
        } else if (mode == 3) {
            int rectangles = rnd.next(1, 4);
            for (int r = 0; r < rectangles; ++r) {
                int r1 = rnd.next(0, n - 1);
                int r2 = rnd.next(r1, n - 1);
                int c1 = rnd.next(0, m - 1);
                int c2 = rnd.next(c1, m - 1);
                for (int i = r1; i <= r2; ++i) {
                    for (int j = c1; j <= c2; ++j) {
                        if (rnd.next() < 0.85) grid[i][j] = 'O';
                    }
                }
            }
        } else if (mode == 4) {
            int offset = rnd.next(-(m - 1), n - 1);
            for (int i = 0; i < n; ++i) {
                int j = i - offset;
                if (0 <= j && j < m) grid[i][j] = 'O';
                if (0 <= j + 1 && j + 1 < m && rnd.next() < 0.45) grid[i][j + 1] = 'O';
                if (0 <= j - 1 && j - 1 < m && rnd.next() < 0.45) grid[i][j - 1] = 'O';
            }
        } else if (mode == 5) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if ((i + j + rnd.next(0, 1)) % 2 == 0) grid[i][j] = 'O';
                }
            }
        } else {
            int seeds = rnd.next(1, min(6, n * m));
            for (int s = 0; s < seeds; ++s) {
                int r = rnd.next(0, n - 1);
                int c = rnd.next(0, m - 1);
                grid[r][c] = 'O';
                if (r > 0 && rnd.next() < 0.55) grid[r - 1][c] = 'O';
                if (r + 1 < n && rnd.next() < 0.55) grid[r + 1][c] = 'O';
                if (c > 0 && rnd.next() < 0.55) grid[r][c - 1] = 'O';
                if (c + 1 < m && rnd.next() < 0.55) grid[r][c + 1] = 'O';
            }
        }
    }

    int cells = n * m;
    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = cells;
    } else if (kMode == 2) {
        k = rnd.next(1, min(cells, max(n, m)));
    } else if (kMode == 3) {
        k = rnd.next(1, min(cells, min(n, m) + 1));
    } else {
        k = rnd.next(1, cells);
    }

    println(n, m, k);
    for (const string& row : grid) printf("%s\n", row.c_str());

    return 0;
}
