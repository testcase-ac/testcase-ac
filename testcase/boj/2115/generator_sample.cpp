#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void printGrid(const vector<string>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }
}

vector<string> makeGrid(int m, int n, char fill) {
    vector<string> grid(m, string(n, fill));
    for (int i = 0; i < m; ++i) {
        grid[i][0] = 'X';
        grid[i][n - 1] = 'X';
    }
    for (int j = 0; j < n; ++j) {
        grid[0][j] = 'X';
        grid[m - 1][j] = 'X';
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m = rnd.next(1, 24);
    int n = rnd.next(1, 24);

    if (mode == 0) {
        m = rnd.any(vector<int>{1, 2, 3, rnd.next(4, 12)});
        n = rnd.any(vector<int>{1, 2, 3, rnd.next(4, 12)});
    }

    vector<string> grid = makeGrid(m, n, 'X');

    if (mode == 1) {
        grid = makeGrid(m, n, '.');
    } else if (mode == 2) {
        grid = makeGrid(m, n, 'X');
        int step = rnd.next(2, 4);
        bool horizontal = rnd.next(0, 1);
        if (horizontal) {
            for (int i = 1; i + 1 < m; ++i) {
                if (i % step != 0) {
                    for (int j = 1; j + 1 < n; ++j) {
                        grid[i][j] = '.';
                    }
                }
            }
        } else {
            for (int j = 1; j + 1 < n; ++j) {
                if (j % step != 0) {
                    for (int i = 1; i + 1 < m; ++i) {
                        grid[i][j] = '.';
                    }
                }
            }
        }
    } else if (mode == 3) {
        grid = makeGrid(m, n, 'X');
        for (int i = 1; i + 1 < m; ++i) {
            for (int j = 1; j + 1 < n; ++j) {
                grid[i][j] = ((i + j + rnd.next(0, 1)) % 3 == 0 ? 'X' : '.');
            }
        }
    } else if (mode == 4) {
        grid = makeGrid(m, n, '.');
        int walls = rnd.next(1, max(1, (m * n) / 12));
        for (int k = 0; k < walls; ++k) {
            if (m <= 2 || n <= 2) {
                break;
            }
            int r1 = rnd.next(1, m - 2);
            int r2 = rnd.next(r1, m - 2);
            int c1 = rnd.next(1, n - 2);
            int c2 = rnd.next(c1, n - 2);
            if (rnd.next(0, 1)) {
                r2 = r1;
            } else {
                c2 = c1;
            }
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    grid[i][j] = 'X';
                }
            }
        }
    } else if (mode == 5) {
        grid = makeGrid(m, n, 'X');
        int rooms = rnd.next(1, 6);
        for (int k = 0; k < rooms; ++k) {
            if (m <= 2 || n <= 2) {
                break;
            }
            int r1 = rnd.next(1, m - 2);
            int r2 = rnd.next(r1, m - 2);
            int c1 = rnd.next(1, n - 2);
            int c2 = rnd.next(c1, n - 2);
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    grid[i][j] = '.';
                }
            }
        }
    } else {
        double wallProb = rnd.next(0.15, 0.65);
        grid = makeGrid(m, n, 'X');
        for (int i = 1; i + 1 < m; ++i) {
            for (int j = 1; j + 1 < n; ++j) {
                grid[i][j] = (rnd.next() < wallProb ? 'X' : '.');
            }
        }
    }

    printGrid(grid);
    return 0;
}
