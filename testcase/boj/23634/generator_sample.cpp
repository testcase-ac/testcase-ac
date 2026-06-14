#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

void printGrid(const Grid& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 22);
    Grid grid(n, string(m, '1'));

    if (mode == 0) {
        int fireCount = rnd.next(0, min(5, n * m));
        for (int k = 0; k < fireCount; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            grid[r][c] = '0';
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = rnd.next(0, 99);
                if (x < 15) {
                    grid[i][j] = '0';
                } else if (x < 35) {
                    grid[i][j] = '2';
                }
            }
        }
    } else if (mode == 2) {
        int stripeGap = rnd.next(2, 5);
        for (int j = rnd.next(0, stripeGap - 1); j < m; j += stripeGap) {
            for (int i = 0; i < n; ++i) {
                grid[i][j] = '2';
            }
            if (n > 1 && rnd.next(0, 1)) {
                grid[rnd.next(0, n - 1)][j] = '1';
            }
        }
        for (int k = 0; k < rnd.next(1, min(6, n * m)); ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            if (grid[r][c] != '2') {
                grid[r][c] = '0';
            }
        }
    } else if (mode == 3) {
        if (n >= 3 && m >= 3) {
            int top = rnd.next(0, n - 3);
            int left = rnd.next(0, m - 3);
            int bottom = rnd.next(top + 2, n - 1);
            int right = rnd.next(left + 2, m - 1);
            for (int i = top; i <= bottom; ++i) {
                grid[i][left] = grid[i][right] = '2';
            }
            for (int j = left; j <= right; ++j) {
                grid[top][j] = grid[bottom][j] = '2';
            }
            grid[rnd.next(top + 1, bottom - 1)][rnd.next(left + 1, right - 1)] = '0';
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '0';
        } else {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '0';
        }
    } else if (mode == 4) {
        int r = rnd.next(0, n - 1);
        for (int j = 0; j < m; ++j) {
            grid[r][j] = '1';
        }
        grid[r][0] = '0';
        grid[r][m - 1] = '0';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i != r && rnd.next(0, 99) < 65) {
                    grid[i][j] = '2';
                }
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + rnd.next(0, 1)) % 5 == 0) ? '2' : '1';
            }
        }
        int fires = rnd.next(1, min(8, n * m));
        for (int k = 0; k < fires; ++k) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '0';
        }
    } else {
        n = rnd.next(1, 3);
        m = rnd.next(1, 5);
        grid.assign(n, string(m, '2'));
        if (rnd.next(0, 1)) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '0';
        }
    }

    printGrid(grid);
    return 0;
}
