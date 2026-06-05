#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 20);
        } else {
            n = rnd.next(1, 20);
            m = 1;
        }
    } else {
        n = rnd.next(2, 15);
        m = rnd.next(2, 15);
    }

    vector<string> grid(n, string(m, '.'));
    int r1 = rnd.next(0, n - 1);
    int c1 = rnd.next(0, m - 1);
    int r2 = rnd.next(0, n - 1);
    int c2 = rnd.next(0, m - 1);

    if (mode == 2 || mode == 3) {
        int wallPercent = (mode == 2) ? rnd.next(5, 35) : rnd.next(55, 85);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next(1, 100) <= wallPercent) {
                    grid[r][c] = 'X';
                }
            }
        }
    } else if (mode == 4) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = 'X';
            }
        }

        r1 = rnd.next(0, n - 1);
        c1 = rnd.next(0, m - 1);
        r2 = rnd.next(0, n - 1);
        c2 = rnd.next(0, m - 1);

        int r = r1;
        int c = c1;
        while (r != r2) {
            grid[r][c] = '.';
            r += (r < r2) ? 1 : -1;
        }
        while (c != c2) {
            grid[r][c] = '.';
            c += (c < c2) ? 1 : -1;
        }
        grid[r2][c2] = rnd.next(0, 1) == 0 ? '.' : 'X';

        int extraOpen = rnd.next(0, min(n * m, 8));
        for (int i = 0; i < extraOpen; ++i) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
        }
    } else if (mode == 5) {
        r2 = r1;
        c2 = c1;
        int wallPercent = rnd.next(20, 75);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next(1, 100) <= wallPercent) {
                    grid[r][c] = 'X';
                }
            }
        }
    } else {
        int wallPercent = rnd.next(0, 70);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next(1, 100) <= wallPercent) {
                    grid[r][c] = 'X';
                }
            }
        }
    }

    grid[r1][c1] = 'X';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }
    println(r1 + 1, c1 + 1);
    println(r2 + 1, c2 + 1);

    return 0;
}
