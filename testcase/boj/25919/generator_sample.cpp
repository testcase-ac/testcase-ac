#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampLevel(int x) {
    return max(1, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, mode == 3 ? 10 : 7);
    int m = rnd.next(2, mode == 3 ? 10 : 7);

    int l = rnd.next(2, 40);
    int e = rnd.next(0, l - 1);
    int k = rnd.next(l, min(10000, l + rnd.next(0, 45)));

    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < 18) {
                    grid[i][j] = -1;
                } else if (roll < 58) {
                    grid[i][j] = 0;
                } else if (roll < 82) {
                    grid[i][j] = clampLevel(l - rnd.next(1, min(l - 1, 8)));
                } else {
                    grid[i][j] = clampLevel(l + rnd.next(0, 12));
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = -1;
            }
        }
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        grid[row][col] = 0;
        while (row != n - 1 || col != m - 1) {
            if (row == n - 1 || (col != m - 1 && rnd.next(0, 1) == 0)) {
                ++col;
            } else {
                ++row;
            }
            int roll = rnd.next(0, 99);
            grid[row][col] = roll < 35 ? 0 : clampLevel(l + rnd.next(-3, 10));
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == -1 && rnd.next(0, 99) < 20) {
                    grid[i][j] = rnd.next(0, 1) == 0 ? 0 : clampLevel(l - rnd.next(1, min(l - 1, 6)));
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i == 1 && j + 1 < m) || (j == m - 2 && i + 1 < n)) {
                    grid[i][j] = clampLevel(l - rnd.next(1, min(l - 1, 5)));
                } else {
                    int roll = rnd.next(0, 99);
                    grid[i][j] = roll < 30 ? -1 : (roll < 55 ? 0 : clampLevel(k + rnd.next(0, 20)));
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = rnd.next(0, 4);
                if (band == 0) {
                    grid[i][j] = -1;
                } else if (band == 1) {
                    grid[i][j] = 0;
                } else if (band == 2) {
                    grid[i][j] = clampLevel(l - rnd.next(1, min(l - 1, 12)));
                } else if (band == 3) {
                    grid[i][j] = clampLevel(l + rnd.next(0, 30));
                } else {
                    grid[i][j] = rnd.next(9000, 10000);
                }
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    auto [si, sj] = cells[0];
    auto [ri, rj] = cells[1];
    grid[si][sj] = -3;
    grid[ri][rj] = -2;

    println(n, m);
    println(l, e, k);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
