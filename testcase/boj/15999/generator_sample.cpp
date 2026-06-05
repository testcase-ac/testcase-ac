#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char flip(char c) {
    return c == 'B' ? 'W' : 'B';
}

vector<string> makeGrid(int n, int m, char fill) {
    return vector<string>(n, string(m, fill));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 14);

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 30);
        } else {
            n = rnd.next(1, 30);
            m = 1;
        }
    } else if (mode >= 5) {
        n = rnd.next(8, 25);
        m = rnd.next(8, 25);
    }

    char base = rnd.next(0, 1) == 0 ? 'B' : 'W';
    vector<string> grid = makeGrid(n, m, base);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(0, 1) == 0 ? 'B' : 'W';
            }
        }
    } else if (mode == 1) {
        char cur = base;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 99) < 35) {
                    cur = flip(cur);
                }
                grid[i][j] = cur;
            }
        }
    } else if (mode == 2) {
        // Uniform grid, with optional sparse flips near borders or center.
        int flips = rnd.next(0, max(1, min(n * m, 6)));
        for (int k = 0; k < flips; ++k) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, m - 1);
            if (rnd.next(0, 2) == 0) {
                i = rnd.any(vector<int>{0, n - 1});
            } else if (rnd.next(0, 1) == 0) {
                j = rnd.any(vector<int>{0, m - 1});
            }
            grid[i][j] = flip(grid[i][j]);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + (base == 'W')) % 2 == 0) ? 'B' : 'W';
            }
        }
    } else if (mode == 4) {
        bool horizontal = rnd.next(0, 1) == 0;
        int run = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = horizontal ? i / run : j / run;
                grid[i][j] = (band % 2 == 0) ? base : flip(base);
            }
        }
    } else if (mode == 5) {
        int h = rnd.next(1, 5);
        int w = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int block = i / h + j / w;
                grid[i][j] = (block % 2 == 0) ? base : flip(base);
            }
        }
    } else if (mode == 6) {
        int rects = rnd.next(2, 8);
        for (int r = 0; r < rects; ++r) {
            int r1 = rnd.next(0, n - 1);
            int r2 = rnd.next(r1, n - 1);
            int c1 = rnd.next(0, m - 1);
            int c2 = rnd.next(c1, m - 1);
            char color = rnd.next(0, 1) == 0 ? 'B' : 'W';
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    grid[i][j] = color;
                }
            }
        }
    } else {
        int blackPercent = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(0, 99) < blackPercent ? 'B' : 'W';
            }
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
