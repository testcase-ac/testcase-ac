#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long smallValue(int band) {
    if (band == 0) {
        return rnd.next(0, 9);
    }
    if (band == 1) {
        return rnd.next(0, 100);
    }
    return rnd.next(999999900LL, 1000000000LL);
}

void printGrid(const vector<vector<long long>>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const auto& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 4) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
    } else {
        n = rnd.next(8, 15);
        m = rnd.next(8, 15);
    }

    int band = rnd.next(0, 2);
    vector<vector<long long>> grid(n, vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = smallValue(band);
        }
    }

    if (mode == 1 || mode == 2) {
        int len = max(n, m);
        long long low = rnd.next(0, 20);
        long long high = rnd.next(999999000LL, 1000000000LL);
        for (int t = 0; t < len; ++t) {
            long long value = (t % 3 == 1 ? high : low + rnd.next(0, 20));
            if (n == 1) {
                grid[0][t] = value;
            } else {
                grid[t][0] = value;
            }
        }
    }

    if (mode >= 3) {
        long long low = rnd.next(0, 30);
        long long high = rnd.next(999999000LL, 1000000000LL);
        int wallRows = rnd.next(0, 2);
        for (int r = 0; r < wallRows; ++r) {
            int row = rnd.next(0, n - 1);
            for (int j = 0; j < m; ++j) {
                grid[row][j] = high;
            }
            grid[row][rnd.next(0, m - 1)] = low;
        }

        int wallCols = rnd.next(0, 2);
        for (int c = 0; c < wallCols; ++c) {
            int col = rnd.next(0, m - 1);
            for (int i = 0; i < n; ++i) {
                grid[i][col] = high;
            }
            grid[rnd.next(0, n - 1)][col] = low;
        }
    }

    if (mode == 4) {
        long long obstacle = rnd.next(100000000LL, 1000000000LL);
        int turns = rnd.next(n + m - 2, n + m + 6);
        int i = 0;
        int j = 0;
        grid[i][j] = rnd.next(0, 10);
        for (int step = 0; step < turns; ++step) {
            if (i == n - 1 && j == m - 1) {
                break;
            }
            bool goDown = (j == m - 1) || (i + 1 < n && rnd.next(0, 1) == 0);
            if (goDown) {
                ++i;
            } else {
                ++j;
            }
            grid[i][j] = rnd.next(0, 10);
        }

        int oi = rnd.next(0, n - 1);
        int oj = rnd.next(0, m - 1);
        grid[oi][oj] = obstacle;
    }

    if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                long long base = (long long)(i + j) * rnd.next(0, 5);
                if ((i + j) % 4 == 0) {
                    base += rnd.next(50, 200);
                }
                grid[i][j] = min(1000000000LL, base);
            }
        }
    }

    grid[0][0] = min(grid[0][0], 1000000000LL);
    grid[n - 1][m - 1] = min(grid[n - 1][m - 1], 1000000000LL);

    printGrid(grid);
    return 0;
}
