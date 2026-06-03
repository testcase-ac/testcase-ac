#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 0) {
        n = rnd.any(vector<int>{1, rnd.next(2, 12), 50});
        m = rnd.any(vector<int>{1, rnd.next(2, 12), 50});
        if (n == 50 && m == 50) {
            if (rnd.next(2) == 0) n = rnd.next(1, 6);
            else m = rnd.next(1, 6);
        }
    } else if (mode == 1) {
        if (rnd.next(2) == 0) {
            n = 1;
            m = rnd.next(1, 50);
        } else {
            n = rnd.next(1, 50);
            m = 1;
        }
    }

    vector<string> grid(n, string(m, 'X'));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = '.';
            }
        }
    } else if (mode == 1) {
        char first = rnd.next(2) ? '.' : 'X';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j) % 2 == 0) ? first : (first == '.' ? 'X' : '.');
            }
        }
    } else if (mode == 2) {
        int period = rnd.next(2, 4);
        bool horizontal = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = horizontal ? i : j;
                grid[i][j] = (band % period == 0) ? 'X' : '.';
            }
        }
    } else if (mode == 3) {
        double floorProb = rnd.next(0.15, 0.9);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (rnd.next() < floorProb) ? '.' : 'X';
            }
        }
    } else if (mode == 4) {
        int r1 = rnd.next(n), r2 = rnd.next(n);
        int c1 = rnd.next(m), c2 = rnd.next(m);
        if (r1 > r2) swap(r1, r2);
        if (c1 > c2) swap(c1, c2);
        for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                grid[i][j] = '.';
            }
        }
        int holes = rnd.next(0, max(0, (r2 - r1 + 1) * (c2 - c1 + 1) / 4));
        for (int k = 0; k < holes; ++k) {
            grid[rnd.next(r1, r2)][rnd.next(c1, c2)] = 'X';
        }
    } else if (mode == 5) {
        int row = rnd.next(n);
        int col = rnd.next(m);
        for (int j = 0; j < m; ++j) grid[row][j] = '.';
        for (int i = 0; i < n; ++i) grid[i][col] = '.';

        int extra = rnd.next(0, n * m / 5);
        for (int k = 0; k < extra; ++k) {
            grid[rnd.next(n)][rnd.next(m)] = '.';
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool border = (i == 0 || i + 1 == n || j == 0 || j + 1 == m);
                grid[i][j] = border ? 'X' : '.';
            }
        }
        if (n <= 2 || m <= 2) {
            grid[rnd.next(n)][rnd.next(m)] = '.';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (rnd.next(100) < 8) ? '.' : 'X';
            }
        }
        grid[rnd.next(n)][rnd.next(m)] = '.';
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
