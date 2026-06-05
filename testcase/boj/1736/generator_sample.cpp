#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;

    if (mode == 7) {
        n = rnd.next(80, 100);
        m = rnd.next(80, 100);
    } else if (mode == 6) {
        n = rnd.next(1, 100);
        m = rnd.next(1, 100);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    }

    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 0) {
        double density = rnd.next(0.0, 0.18);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next() < density;
            }
        }
    } else if (mode == 1) {
        double density = rnd.next(0.55, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next() < density;
            }
        }
    } else if (mode == 2) {
        int step = rnd.next(1, max(1, min(n, m) / 2 + 1));
        int offset = rnd.next(0, max(0, step - 1));
        for (int i = 0; i < n; ++i) {
            int j = (i + offset) % step;
            while (j < m) {
                if (i + j < n + m - 1 && rnd.next(0, 2) != 0) {
                    grid[i][j] = 1;
                }
                j += step;
            }
        }
    } else if (mode == 3) {
        int count = rnd.next(1, min(n, m));
        for (int k = 0; k < count; ++k) {
            int i = k * n / count;
            int j = m - 1 - k * m / count;
            grid[i][j] = 1;
        }
    } else if (mode == 4) {
        int chains = rnd.next(1, min(4, n));
        for (int c = 0; c < chains; ++c) {
            int row = rnd.next(0, n - 1);
            int col = rnd.next(0, m - 1);
            int len = rnd.next(1, n + m - 1);
            for (int t = 0; t < len; ++t) {
                grid[row][col] = 1;
                if (row + 1 == n && col + 1 == m) break;
                if (row + 1 == n || (col + 1 < m && rnd.next(0, 1) == 0)) {
                    ++col;
                } else {
                    ++row;
                }
            }
        }
    } else if (mode == 5) {
        int threshold = rnd.next(0, n + m - 2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool onBoundary = (i + j == threshold);
                bool nearBoundary = abs(i + j - threshold) == 1 && rnd.next(0, 3) == 0;
                grid[i][j] = onBoundary || nearBoundary;
            }
        }
    } else if (mode == 6) {
        double density = rnd.next(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next() < density;
            }
        }
    } else {
        int stripes = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool stripe = ((i + j) % stripes == 0);
                grid[i][j] = stripe && rnd.next(0, 4) != 0;
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
