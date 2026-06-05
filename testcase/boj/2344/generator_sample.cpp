#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 4) {
        n = rnd.next(6, 16);
        m = rnd.next(2, 7);
    } else if (mode == 5) {
        n = rnd.next(2, 7);
        m = rnd.next(6, 16);
    } else {
        n = rnd.next(8, 20);
        m = rnd.next(8, 20);
    }

    vector<vector<int>> grid(n, vector<int>(m));

    if (mode <= 1) {
        int streak = rnd.next(1, 4);
        int phase = rnd.next(0, streak - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + phase) / streak) % 2;
            }
        }
    } else if (mode == 2) {
        int mask = rnd.next(0, (1 << (n * m)) - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (mask >> (i * m + j)) & 1;
            }
        }
    } else if (mode == 3) {
        int fill = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = fill;
            }
        }
        int changes = rnd.next(1, n * m);
        for (int k = 0; k < changes; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            grid[r][c] ^= 1;
        }
    } else if (mode == 4 || mode == 5) {
        int band = rnd.next(2, 5);
        int offset = rnd.next(0, band - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + offset) % band == 0);
            }
        }
    } else {
        int pattern = rnd.next(0, 2);
        double flipChance = rnd.next(0.0, 0.18);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pattern == 0) {
                    grid[i][j] = (i + j) % 2;
                } else if (pattern == 1) {
                    grid[i][j] = (i % 3 == j % 3);
                } else {
                    grid[i][j] = rnd.next(0, 99) < rnd.next(15, 85);
                }
                if (rnd.next() < flipChance) {
                    grid[i][j] ^= 1;
                }
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
