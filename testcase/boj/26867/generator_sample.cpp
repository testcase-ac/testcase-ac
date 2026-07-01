#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 12));
    vector<string> grid(n, string(n, '.'));

    if (mode == 0) {
        grid[0][0] = rnd.any(string(".#?"));
    } else if (mode == 1) {
        string chars = ".#?";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.any(chars);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < 55) {
                    grid[i][j] = '?';
                } else if (roll < 75) {
                    grid[i][j] = '#';
                } else {
                    grid[i][j] = '.';
                }
            }
        }
    } else if (mode == 3) {
        int row = rnd.next(0, n - 1);
        int left = rnd.next(0, n - 2);
        int right = rnd.next(left + 1, n - 1);
        for (int j = left; j <= right; ++j) {
            grid[row][j] = '?';
        }
        if (left > 0) {
            grid[row][left - 1] = '#';
        }
        if (right + 1 < n) {
            grid[row][right + 1] = '#';
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == row && j >= left && j <= right) {
                    continue;
                }
                if (grid[i][j] == '.' && rnd.next(0, 99) < 25) {
                    grid[i][j] = rnd.any(string("#?"));
                }
            }
        }
    } else if (mode == 4) {
        int col = rnd.next(0, n - 1);
        int top = rnd.next(0, n - 2);
        int bottom = rnd.next(top + 1, n - 1);
        for (int i = top; i <= bottom; ++i) {
            grid[i][col] = '?';
        }
        if (top > 0) {
            grid[top - 1][col] = '#';
        }
        if (bottom + 1 < n) {
            grid[bottom + 1][col] = '#';
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == col && i >= top && i <= bottom) {
                    continue;
                }
                if (grid[i][j] == '.' && rnd.next(0, 99) < 25) {
                    grid[i][j] = rnd.any(string("#?"));
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0 || i + 1 == n || j + 1 == n) {
                    grid[i][j] = rnd.next(0, 99) < 65 ? '#' : '?';
                } else if ((i + j + rnd.next(0, 1)) % 3 == 0) {
                    grid[i][j] = '?';
                } else {
                    grid[i][j] = rnd.next(0, 99) < 20 ? '#' : '.';
                }
            }
        }
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
