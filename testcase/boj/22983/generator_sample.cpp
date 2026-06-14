#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char chessCell(int i, int j, char topLeft) {
    bool flip = ((i + j) % 2 == 1);
    if (!flip) return topLeft;
    return topLeft == 'B' ? 'W' : 'B';
}

void flipCell(vector<string>& grid, int i, int j) {
    grid[i][j] = grid[i][j] == 'B' ? 'W' : 'B';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);

    if (mode == 1) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 24);
    } else if (mode == 2) {
        n = rnd.next(1, 24);
        m = rnd.next(1, 4);
    } else if (mode == 3) {
        n = rnd.next(8, 28);
        m = rnd.next(8, 28);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{1, 2, 3, 5, 13, 21});
        m = rnd.any(vector<int>{1, 2, 4, 7, 12, 23});
    } else if (mode == 6) {
        n = rnd.next(25, 40);
        m = rnd.next(25, 40);
    }

    vector<string> grid(n, string(m, 'B'));
    char topLeft = rnd.next(0, 1) == 0 ? 'B' : 'W';

    if (mode == 0 || mode == 1 || mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = chessCell(i, j, topLeft);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = chessCell(i, j, topLeft);
            }
        }

        int defects = rnd.next(1, max(1, n * m / 8));
        for (int t = 0; t < defects; ++t) {
            flipCell(grid, rnd.next(0, n - 1), rnd.next(0, m - 1));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            char rowColor = rnd.next(0, 1) == 0 ? 'B' : 'W';
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(0, 4) == 0 ? chessCell(i, j, topLeft) : rowColor;
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(0, 1) == 0 ? 'B' : 'W';
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char expected = chessCell(i, j, topLeft);
                grid[i][j] = rnd.next(0, 9) < 8 ? expected : (expected == 'B' ? 'W' : 'B');
            }
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
