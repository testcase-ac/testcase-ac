#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 4);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(6, 14);
        m = rnd.next(6, 14);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 20);
    } else {
        n = rnd.next(10, 20);
        m = rnd.next(10, 20);
    }

    vector<string> grid(n, string(m, '#'));

    if (mode == 0 || mode == 1) {
        double landProbability = rnd.next(0.25, 0.95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < landProbability) {
                    grid[i][j] = '.';
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0) ? '.' : '#';
            }
        }
    } else if (mode == 3) {
        double waterProbability = rnd.next(0.10, 0.35);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (rnd.next() < waterProbability) ? '#' : '.';
            }
        }
    } else if (mode == 4) {
        int rowPeriod = rnd.next(2, 4);
        int colPeriod = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool inStripe = (i % rowPeriod == 0) || (j % colPeriod == 0);
                grid[i][j] = inStripe ? '.' : '#';
            }
        }
    } else {
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(0, m - 1);
        int c2 = rnd.next(c1, m - 1);
        for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                grid[i][j] = '.';
            }
        }
        int extra = rnd.next(0, n * m / 5);
        while (extra--) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
        }
    }

    bool hasLand = false;
    for (const string& row : grid) {
        hasLand = hasLand || row.find('.') != string::npos;
    }
    if (!hasLand) {
        grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
