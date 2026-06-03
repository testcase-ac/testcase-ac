#include "testlib.h"

#include <array>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);

    vector<string> grid(n, string(m, '0'));
    vector<Point> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    if (mode == 0) {
        int density = rnd.next(0, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < density) {
                    grid[i][j] = '1';
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = '1';
            }
        }

        int row = rnd.next(0, n - 1);
        int left = rnd.next(0, m - 1);
        int len = rnd.next(1, m - left);
        for (int j = left; j < left + len; ++j) {
            grid[row][j] = '0';
        }
        if (n > 2 && rnd.next(2) == 0) {
            int col = rnd.next(0, m - 1);
            for (int i = 0; i < n; ++i) {
                grid[i][col] = '0';
            }
        }
    } else if (mode == 2) {
        int wallRow = rnd.next(0, n - 1);
        int gap = rnd.next(0, m - 1);
        for (int j = 0; j < m; ++j) {
            grid[wallRow][j] = (j == gap ? '0' : '1');
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '0' && rnd.next(100) < 20) {
                    grid[i][j] = '1';
                }
            }
        }
        grid[wallRow][gap] = '0';
    } else if (mode == 3) {
        int density = rnd.next(55, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < density) {
                    grid[i][j] = '1';
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j + rnd.next(2)) % 3 == 0) {
                    grid[i][j] = '1';
                }
            }
        }
    }

    array<char, 4> special = {'2', '3', '4', '5'};
    for (int idx = 0; idx < 4; ++idx) {
        auto [r, c] = cells[idx];
        grid[r][c] = special[idx];
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
